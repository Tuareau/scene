#include "parallelepiped.h"

namespace tua {

	Parallelepiped::Parallelepiped(std::vector<Polygon> & polygons)
		: Figure(polygons) {}

	Parallelepiped::Parallelepiped(Point base, size_t height, size_t width, size_t depth) {
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

		_polygons.emplace_back(pts0);
		_polygons.emplace_back(pts1);
		_polygons.emplace_back(pts2);
		_polygons.emplace_back(pts3);
		_polygons.emplace_back(pts4);
		_polygons.emplace_back(pts5);
	}

	void Parallelepiped::set_polygons_visibility() {
		auto less_aver_point_depth {
			[](const auto & polygon0, const auto & polygon1) {
				return polygon0.average_point().z() < polygon1.average_point().z();
			}
		};
		std::sort(_polygons.begin(), _polygons.end(), less_aver_point_depth);
		const auto half = _polygons.size() / 2;
		for (size_t i = 0; i < _polygons.size(); ++i) {
			if (i < half)
				_polygons[i].set_visibility(false);
			else 
				_polygons[i].set_visibility(true);
		}
	}

	void Parallelepiped::draw() const {
		for (const auto & pol : _polygons)
			pol.draw();
	}

}
