#include "polygon.h"

namespace tua {

	Polygon::Polygon()
		: _is_visible(false)	{}

	Polygon::Polygon(std::vector<Point *> & points) 
		: _points(points), _is_visible(true) {}

	Polygon::Polygon(const Polygon & other) {
		_is_visible = other._is_visible;
		for (const auto & point : other._points) {
			Point * pt = new Point(*point);
			_points.push_back(pt);
		}
	}

	Polygon::~Polygon() {
		for (auto ptr : _points) delete ptr;
	}

	void Polygon::draw() const {
		using std::round;
		if (!_is_visible) return;

		auto curr = _points.begin();
		auto next = std::next(_points.begin());
		const auto penultimate = std::prev(_points.end());

		int x0 = round((*curr)->x());
		int y0 = round((*curr)->y());
		int x1 = round((*penultimate)->x());
		int y1 = round((*penultimate)->y());

		setcolor(WHITE);
		line(x0, y0, x1, y1);

		while (next != _points.end()) {
			x0 = round((*curr)->x());
			y0 = round((*curr)->y());
			x1 = round((*next)->x());
			y1 = round((*next)->y());
			line(x0, y0, x1, y1);
			++curr; ++next;
		}			
	}

	size_t Polygon::size() const {
		return _points.size();
	}

	Point * Polygon::operator[](size_t idx) {
		return _points.at(idx);
	}

	template<typename... Points>
	Polygon make_polygon(Points... point) {
		std::vector<Point *> points;
		Point * new_point = new Point(point);
		points.push_back(new_point)...;
		return Polygon(points);
	}
}