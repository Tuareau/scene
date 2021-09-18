#include "polygon.h"

namespace tua {

	Polygon::Polygon()
		: _is_visible(false) {}

	Polygon::Polygon(std::vector<Point> & points) 
		: _is_visible(true) {
		_polygon_matrix = new Matrix(points);
	}

	Polygon::Polygon(const Polygon & other) {
		_is_visible = other._is_visible;
		_polygon_matrix = new Matrix(*other._polygon_matrix);
	}

	Polygon::Polygon(Polygon && other) {
		_is_visible = other._is_visible;
		_polygon_matrix = other._polygon_matrix;
		other._polygon_matrix = nullptr;
	}

	const std::vector<Point>& Polygon::points() const {
		return _polygon_matrix->points();
	}

	void Polygon::draw() const {
		using std::round;
		if (!_is_visible || _polygon_matrix->size() < 1) 
			return;

		auto msize = _polygon_matrix->size();
		const auto & matrix = *_polygon_matrix;

		const auto curr = matrix[0];
		const auto penultimate = matrix[msize - 1];

		int x0 = round(curr.x());
		int y0 = round(curr.y());
		int x1 = round(penultimate.x());
		int y1 = round(penultimate.y());
		setcolor(WHITE);
		line(x0, y0, x1, y1);

		for (size_t i = 0; i < msize - 1; ++i) {
			const auto pt0 = matrix[i];
			const auto pt1 = matrix[i + 1];
			x0 = round(pt0.x());
			y0 = round(pt0.y());
			x1 = round(pt1.x());
			y1 = round(pt1.y());
			line(x0, y0, x1, y1);
		}			
	}

	Polygon::~Polygon() {
		delete _polygon_matrix;
	}

	void Polygon::displace(Sides side, double step, const Point & base) {
		switch (side) {
			case Sides::LEFT:
				_polygon_matrix->shear(-step, 0, 0, base);
			case Sides::UP:
				_polygon_matrix->shear(0, -step, 0, base);
			case Sides::RIGHT:
				_polygon_matrix->shear(step, 0, 0, base);
			case Sides::DOWN:
				_polygon_matrix->shear(0, step, 0, base);
			case Sides::FURTHER:
				_polygon_matrix->shear(0, 0, -step, base);
			case Sides::CLOSER:
				_polygon_matrix->shear(0, 0, step, base);
		}
	}

	void Polygon::scale(double coef, const Point & base) {
		_polygon_matrix->scale(coef, base);
	}

	void Polygon::spin(Axes axis, double angle, const Point & base) {
		switch (axis) {
			case Axes::X:
				_polygon_matrix->rotate(angle, Axes::X, base);
			case Axes::Y:
				_polygon_matrix->rotate(angle, Axes::Y, base);
			case Axes::Z:
				_polygon_matrix->rotate(angle, Axes::Z, base);
		}
	}

	Point Polygon::average_point() const {
		return _polygon_matrix->average_point();
	}
}