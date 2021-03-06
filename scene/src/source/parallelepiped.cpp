#include "parallelepiped.h"
#include "polygon.h"

namespace tua {

	Parallelepiped::Parallelepiped(Point base, size_t width, size_t height, size_t depth, Color color)
		: Figure(color) {
		Point pt0(base);
		Point pt1(base.x(), base.y(), base.z() - depth);
		Point pt2(base.x() + width, base.y(), base.z() - depth);
		Point pt3(base.x() + width, base.y(), base.z());
		Point pt4(base.x(), base.y() + height, base.z());
		Point pt5(base.x(), base.y() + height, base.z() - depth);
		Point pt6(base.x() + width, base.y() + height, base.z() - depth);
		Point pt7(base.x() + width, base.y() + height, base.z());

		std::vector<Point> pts0 = { pt0, pt1, pt2, pt3 };
		std::vector<Point> pts1 = { pt0, pt4, pt7, pt3 };
		std::vector<Point> pts2 = { pt0, pt1, pt5, pt4 };
		std::vector<Point> pts3 = { pt6, pt7, pt3, pt2 };
		std::vector<Point> pts4 = { pt6, pt5, pt1, pt2 };
		std::vector<Point> pts5 = { pt6, pt5, pt4, pt7 };

		_polygons.emplace_back(pts0, this->type(), color);
		_polygons.emplace_back(pts1, this->type(), color);
		_polygons.emplace_back(pts2, this->type(), color);
		_polygons.emplace_back(pts3, this->type(), color);
		_polygons.emplace_back(pts4, this->type(), color);
		_polygons.emplace_back(pts5, this->type(), color);
	}

	Figure::FigureType Parallelepiped::type() const {
		return Figure::FigureType::PARALLELEPIPED;
	}
	
}
