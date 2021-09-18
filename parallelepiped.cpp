#include "parallelepiped.h"

namespace tua {

	Parallelepiped::Parallelepiped(std::vector<Polygon> & polygons) 
		: Figure(polygons) {}

	Parallelepiped::Parallelepiped(Point base, int height, int width, int depth) {
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
		std::vector<Point> pts4 = { pt6, pt5, pt1, pt7 };
		std::vector<Point> pts5 = { pt6, pt5, pt4, pt7 };

		Polygon pol0(pts0);
		Polygon pol1(pts1);
		Polygon pol2(pts2);
		Polygon pol3(pts3);
		Polygon pol4(pts4);
		Polygon pol5(pts5);

		_polygons.push_back(pol0);
		_polygons.push_back(pol1);
		_polygons.push_back(pol2);
		_polygons.push_back(pol3);
		_polygons.push_back(pol4);
	}

	void Parallelepiped::displace(Sides side, double step) {
		for (auto pol : _polygons)
			pol.displace(side, step);
	}

	void Parallelepiped::scale(double coef) {
		for (auto pol : _polygons)
			pol.scale(coef);
	}

	void Parallelepiped::spin(Axes axis, double angle) {
		for (auto pol : _polygons)
			pol.spin(axis, angle);
	}

	void Parallelepiped::draw() const {
		for (const auto & pol : _polygons)
			pol.draw();
	}

}
