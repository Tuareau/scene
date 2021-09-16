#include "parallelepiped.h"

namespace tua {

	Parallelepiped::Parallelepiped(std::vector<Polygon>& polygons) 
		: Figure(polygons) {
		fill_matrix();
	}

	Parallelepiped::Parallelepiped(Point base, int height, int width, int depth) {
		Point * pt0 = new Point(base);
		Point * pt1 = new Point(base.x(), base.y(), base.z() - depth);
		Point * pt2 = new Point(base.x() + width, base.y(), base.z() - depth);
		Point * pt3 = new Point(base.x() + width, base.y(), base.z());
		Point * pt4 = new Point(base.x(), base.y() + height, base.z());
		Point * pt5 = new Point(base.x(), base.y() + height, base.z() - depth);
		Point * pt6 = new Point(base.x() + width, base.y() + height, base.z() - depth);
		Point * pt7 = new Point(base.x() + width, base.y() + height, base.z());

		std::vector<Point *> pts0 = { pt0, pt1, pt2, pt3 };
		std::vector<Point *> pts1 = { pt0, pt4, pt7, pt3 };
		std::vector<Point *> pts2 = { pt0, pt1, pt5, pt4 };
		std::vector<Point *> pts3 = { pt6, pt7, pt3, pt2 };
		std::vector<Point *> pts4 = { pt6, pt5, pt1, pt7 };
		std::vector<Point *> pts5 = { pt6, pt5, pt4, pt7 };

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

		fill_matrix();
	}

	void Parallelepiped::displace(Sides side, double step) {

	}

	void Parallelepiped::scale(double coef) {

	}

	void Parallelepiped::spin(Axes axis, double angle) {

	}

	void Parallelepiped::draw(Matrix * z_buffer) const {
		for (const auto & polygon : _polygons)
			polygon.draw();
	}

	void Parallelepiped::fill_depth_buffer(Matrix * z_buffer) const {

	}

	/*
	void shear(double dx, double dy, double dz);
	void rotate(double angle, Axes axis);
	void scale(double coef);
	*/
}
