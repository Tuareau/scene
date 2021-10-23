#include "polygon.h"
#include "depthbuffer.h"
#include "pixel.h"

namespace tua {

	Polygon::Polygon(const std::vector<Point> & points, Figure::FigureType type, Color color) {
		_polygon_matrix = new Matrix(points);
		_points_count = static_cast<PolygonPointsCount>(_polygon_matrix->size());
		_figure_type = type;
		_filling_color = color;
	}

	Polygon::Polygon(const Polygon & other) {
		_polygon_matrix = new Matrix(*other._polygon_matrix);
		_points_count = static_cast<PolygonPointsCount>(_polygon_matrix->size());
		_figure_type = other._figure_type;
		_filling_color =other._filling_color;
	}

	Polygon & Polygon::operator=(const Polygon & other) {
		_polygon_matrix = new Matrix(*other._polygon_matrix);
		_points_count = static_cast<PolygonPointsCount>(_polygon_matrix->size());
		_figure_type = other._figure_type;
		_filling_color = other._filling_color;
		return *this;
	}
	
	Polygon::Polygon(Polygon && other) noexcept {
		_polygon_matrix = other._polygon_matrix;
		other._polygon_matrix = nullptr;
		_points_count = static_cast<PolygonPointsCount>(_polygon_matrix->size());
		_figure_type = other._figure_type;
		_filling_color = other._filling_color;
	}	
	
	Polygon::~Polygon() {
		delete _polygon_matrix;
	}

	Polygon & Polygon::operator=(Polygon && other) noexcept {
		_polygon_matrix = other._polygon_matrix;
		other._polygon_matrix = nullptr;
		_points_count = static_cast<PolygonPointsCount>(_polygon_matrix->size());
		_figure_type = other._figure_type;
		_filling_color = other._filling_color;
		return *this;
	}

	const std::vector<Point> & Polygon::points() const {
		return _polygon_matrix->points();
	}

	void Polygon::displace(Sides side, double step) {
		switch (side) {
			case Sides::LEFT:
				_polygon_matrix->shear(-step, 0, 0);
				break;
			case Sides::RIGHT:
				_polygon_matrix->shear(step, 0, 0);
				break;
			case Sides::UP:
				_polygon_matrix->shear(0, -step, 0);
				break;
			case Sides::DOWN:
				_polygon_matrix->shear(0, step, 0);
				break;
			case Sides::FURTHER:
				_polygon_matrix->shear(0, 0, -step);
				break;
			case Sides::CLOSER:
				_polygon_matrix->shear(0, 0, step);
				break;
		}
	}

	void Polygon::scale(double coef, const Point & base) {
		_polygon_matrix->scale(coef, base);
	}

	void Polygon::spin(Axes axis, double angle, const Point & base) {
		switch (axis) {
			case Axes::X:
				_polygon_matrix->rotate(angle, Axes::X, base);
				break;
			case Axes::Y:
				_polygon_matrix->rotate(angle, Axes::Y, base);
				break;
			case Axes::Z:
				_polygon_matrix->rotate(angle, Axes::Z, base);
				break;
		}
	}

	Point Polygon::average_point() const {
		return _polygon_matrix->average_point();
	}

	void Polygon::fill_depth_buffer(DepthBuffer * z_buffer) {
		std::vector<Pixel> edge_pixels;
		const auto & matrix = *_polygon_matrix;
		if (_points_count == PolygonPointsCount::THREE) {
			const Point & first = matrix[0];
			const Point & second = matrix[1];
			const Point & third = matrix[2];

			edge_pixels = collect_pixels(second, third);
			fill_area(z_buffer, { first, edge_pixels });
		}
		else if (_points_count == PolygonPointsCount::FOUR) {
			const Point & first = matrix[0];
			const Point & second = matrix[1];
			const Point & third = matrix[2];
			const Point & fourth = matrix[3];

			edge_pixels = collect_pixels(first, third);
			fill_area(z_buffer, { second, edge_pixels });
			fill_area(z_buffer, { fourth, edge_pixels });
		}
		else {
			throw std::logic_error("Polygon::fill_depth_buffer(): this count of polygon points is not allowed yet");
		}
		fill_edges(z_buffer);
	}

	void Polygon::paint_pixels(std::vector<Pixel> & pixels, Color color) {
		for (auto & pixel : pixels) {
			pixel[0].color = color;
		}
	}

	void Polygon::identify_pixels_with_figure(std::vector<Pixel> & pixels) {
		for (auto & pixel : pixels) {
			pixel[0].object_type = _figure_type;
		}
	}

	void Polygon::fill_area(DepthBuffer * z_buffer, PolygonArea area) {
		for (auto & pixel : area.second) {
			Point curr(pixel.x(), pixel.y(), pixel[0].z);
			auto inner_pixels = collect_pixels(area.first, curr);
			paint_pixels(inner_pixels, _filling_color);
			identify_pixels_with_figure(inner_pixels);
			fill_line(z_buffer, inner_pixels);
			inner_pixels.erase(inner_pixels.begin(), inner_pixels.end());
		}
	}

	void Polygon::fill_edges(DepthBuffer * z_buffer, Color color) {
		const auto & points = (*_polygon_matrix).points();
		const auto & first = points[0];
		const auto & last = points[points.size() - 1];

		auto edge = collect_pixels(first, last);
		paint_pixels(edge, Color::WHITE);
		identify_pixels_with_figure(edge);
		fill_line(z_buffer, edge);

		for (size_t i = 0; i < points.size() - 1; ++i) {
			const auto & pt0 = points[i];
			const auto & pt1 = points[i + 1];

			auto edge = collect_pixels(pt0, pt1);
			paint_pixels(edge, Color::WHITE);
			identify_pixels_with_figure(edge);
			fill_line(z_buffer, edge);
		}
	}

	void Polygon::fill_line(DepthBuffer * z_buffer, const std::vector<Pixel> & pixels) {
		for (const auto & pixel : pixels) {
			int x = pixel.x(), y = pixel.y();
			if (x >= static_cast<int>(z_buffer->width()) || x < 0) {
				continue;
			}
			if (y >= static_cast<int>(z_buffer->height()) || y < 0) {
				continue;
			}			
			(*z_buffer)(x, y).push_depth(pixel[0]);
		}
	}

	std::vector<Pixel> Polygon::collect_pixels(const Point & p1, const Point & p2) const {
		using std::round;
		using std::abs;

		auto x1 = static_cast<int>(round(p1.x()));
		auto y1 = static_cast<int>(round(p1.y()));
		auto z1 = static_cast<int>(round(p1.z()));

		auto x2 = static_cast<int>(round(p2.x()));
		auto y2 = static_cast<int>(round(p2.y()));
		auto z2 = static_cast<int>(round(p2.z()));

		Depth d = {
			z1,
			Figure::FigureType::NONE,
			Color::BLACK,
		};
		Pixel px(x1, y1);
		px.push_depth(d);

		std::vector<Pixel> pixels;
		pixels.push_back(px);

		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		int dz = abs(z2 - z1);

		int xs, ys, zs;
		(x2 > x1) ? xs = 1 : xs = -1;
		(y2 > y1) ? ys = 1 : ys = -1;
		(z2 > z1) ? zs = 1 : zs = -1;

		int e1, e2;
		// X
		if (dx >= dy && dx >= dz) {
			e1 = 2 * dy - dx;
			e2 = 2 * dz - dx;
			while (x1 != x2) {
				x1 += xs;
				if (e1 >= 0) {
					y1 += ys;
					e1 -= 2 * dx;
				}
				if (e2 >= 0) {
					z1 += zs;
					e2 -= 2 * dx;
				}
				e1 += 2 * dy;
				e2 += 2 * dz;

				Depth d = {
					z1,
					Figure::FigureType::NONE,
					Color::BLACK,
				};
				Pixel px(x1, y1);
				px.push_depth(d);
				pixels.push_back(px);
			}
		}
		// Y
		else if (dy >= dx && dy >= dz) {
			e1 = 2 * dx - dy;
			e2 = 2 * dz - dy;
			while (y1 != y2) {
				y1 += ys;
				if (e1 >= 0) {
					x1 += xs;
					e1 -= 2 * dy;
				}
				if (e2 >= 0) {
					z1 += zs;
					e2 -= 2 * dy;
				}
				e1 += 2 * dx;
				e2 += 2 * dz;
				Depth d = {
					z1,
					Figure::FigureType::NONE,
					Color::BLACK,
				};
				Pixel px(x1, y1);
				px.push_depth(d);
				pixels.push_back(px);
			}
		}
		// Z
		else {
			e1 = 2 * dy - dz;
			e2 = 2 * dx - dz;
			while (z1 != z2) {
				z1 += zs;
				if (e1 >= 0) {
					y1 += ys;
					e1 -= 2 * dz;
				}
				if (e2 >= 0) {
					x1 += xs;
					e2 -= 2 * dz;
				}
				e1 += 2 * dy;
				e2 += 2 * dx;
				Depth d = {
					z1,
					Figure::FigureType::NONE,
					Color::BLACK,
				};
				Pixel px(x1, y1);
				px.push_depth(d);
				pixels.push_back(px);
			}
		}			   
		return pixels;
	}

}