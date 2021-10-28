#include "ground.h"

namespace tua {

	Ground::Ground(size_t width, size_t length, int y_level, Color color)
		: Figure(color) {
		Point pt0(  0.0, y_level, -static_cast<double>(width / 2));
		Point pt1(length, y_level, -static_cast<double>(width / 2));
		Point pt2(length, y_level, static_cast<double>(width / 2));
		Point pt3(  0.0, y_level, static_cast<double>(width / 2));

		std::vector<Point> pts0 = { pt0, pt1, pt2, pt3 };

		_polygons.emplace_back(pts0, this->type(), color);
	}

	Figure::FigureType Ground::type() const {
		return Figure::FigureType::GROUND;
	}

}