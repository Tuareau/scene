#include "polygon.h"

namespace tua {

	Polygon::Polygon()
		: _polygon_matrix(nullptr) {}

	Polygon::Polygon(const std::vector<Point> & points) {
		_polygon_matrix = new Matrix(points);
	}

	Polygon::Polygon(const Polygon & other) {
		_polygon_matrix = new Matrix(*other._polygon_matrix);
	}

	Polygon & Polygon::operator=(const Polygon & other) {
		_polygon_matrix = new Matrix(*other._polygon_matrix);
		return *this;
	}
	
	Polygon::Polygon(Polygon && other) noexcept {
		_polygon_matrix = other._polygon_matrix;
		other._polygon_matrix = nullptr;
	}	
	
	Polygon::~Polygon() {
		delete _polygon_matrix;
	}

	Polygon & Polygon::operator=(Polygon && other) noexcept {
		_polygon_matrix = other._polygon_matrix;
		other._polygon_matrix = nullptr;
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

	void Polygon::fill_depth_buffer(DepthBuffer * z_buffer, int color) {
		const auto points_count = _polygon_matrix->size();
		std::vector<Pixel> edge_pixels;
		std::vector<Pixel> inner_pixels;
		if (points_count == 3) {
			const Point & first = (*_polygon_matrix)[0];
			const Point & second = (*_polygon_matrix)[1];
			const Point & third = (*_polygon_matrix)[2];

			edge_pixels = std::move(collect_pixels(second, third));
			for (const auto & pixel : edge_pixels) {
				Point curr(pixel.x(), pixel.y(), pixel.depth());
				inner_pixels = std::move(collect_pixels(first, curr));
				fill_pixels(z_buffer, inner_pixels, color);
				inner_pixels.erase(inner_pixels.begin(), inner_pixels.end());
			}
		}
		else if (points_count == 4) {
			const Point & first = (*_polygon_matrix)[0];
			const Point & second = (*_polygon_matrix)[1];
			const Point & third = (*_polygon_matrix)[2];
			const Point & fourth = (*_polygon_matrix)[3];

			edge_pixels = std::move(collect_pixels(first, third));
			for (const auto & pixel : edge_pixels) {
				Point curr(pixel.x(), pixel.y(), pixel.depth());
				inner_pixels = std::move(collect_pixels(second, curr));
				fill_pixels(z_buffer, inner_pixels, color);
				inner_pixels.erase(inner_pixels.begin(), inner_pixels.end());
			}
			for (const auto & pixel : edge_pixels) {
				Point curr(pixel.x(), pixel.y(), pixel.depth());
				inner_pixels = std::move(collect_pixels(fourth, curr));
				fill_pixels(z_buffer, inner_pixels, color);
				inner_pixels.erase(inner_pixels.begin(), inner_pixels.end());
			}
		}
		fill_edges(z_buffer, WHITE);
	}

	void Polygon::fill_edges(DepthBuffer * z_buffer, int color) {
		const auto & points = (*_polygon_matrix).points();
		const auto & first = points[0];
		const auto & last = points[points.size() - 1];

		const auto edge = std::move(collect_pixels(first, last));
		fill_pixels(z_buffer, edge, color);

		for (size_t i = 0; i < points.size() - 1; ++i) {
			const auto & pt0 = points[i];
			const auto & pt1 = points[i + 1];
			const auto edge = std::move(collect_pixels(pt0, pt1));
			fill_pixels(z_buffer, edge, color);
		}
	}

	void Polygon::fill_pixels(DepthBuffer * z_buffer, const std::vector<Pixel>& pixels, int color) {
		for (const auto & pixel : pixels) {
			int x = pixel.x(), y = pixel.y(), z = pixel.depth();
			if (x >= z_buffer->width() || x < 0)
				continue;
			if (y >= z_buffer->height() || y < 0)
				continue;
			if (z >= (*z_buffer)(x, y).depth()) {
				(*z_buffer)(x, y).set_depth(z);
				(*z_buffer)(x, y).set_color(color);
			}
		}
	}

	std::vector<Pixel> Polygon::collect_pixels(const Point & p1, const Point & p2) const {
		using std::round;
		using std::abs;

		auto x1 = int(round(p1.x()));
		auto y1 = int(round(p1.y()));
		auto z1 = int(round(p1.z()));

		auto x2 = int(round(p2.x()));
		auto y2 = int(round(p2.y()));
		auto z2 = int(round(p2.z()));

		std::vector<Pixel> pixels;
		pixels.emplace_back(x1, y1, z1);

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
				pixels.emplace_back(x1, y1, z1);
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
				pixels.emplace_back(x1, y1, z1);
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
				pixels.emplace_back(x1, y1, z1);
			}
		}			   
		return pixels;
	}

}