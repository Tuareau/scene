#include "figure.h"

namespace tua {

	Figure::Figure(std::vector<Polygon> & polygons, int color)
		: _polygons(polygons), _color(color) {}

	Figure::Figure(int color) : _color(color) {}

	int Figure::color() const {
		return _color;
	}

	Point Figure::average_point() const
	{		
		std::vector<Point> points;
		for (const auto & polygon : _polygons) {
			const auto & pts = polygon.points();
			points.insert(points.end(), pts.begin(), pts.end());
		}

		double aver_x = 0.0, aver_y = 0.0, aver_z = 0.0;
		for (const auto & point : points) {
			aver_x += point.x();
			aver_y += point.y();
			aver_z += point.z();
		}
		aver_x /= points.size();
		aver_y /= points.size();
		aver_z /= points.size();
		return Point(aver_x, aver_y, aver_z);
	}

	void Figure::displace(Sides side, double step) {
		for (auto & pol : _polygons)
			pol.displace(side, step);
	}

	void Figure::scale(double coef) {
		for (auto & pol : _polygons)
			pol.scale(coef, Figure::average_point());
	}

	void Figure::spin(Axes axis, double angle) {
		for (auto & pol : _polygons)
			pol.spin(axis, angle, Figure::average_point());
	}

	Bounds Figure::bounds() const {		
		using std::round;
		const auto & pts0 = _polygons[0].points();
		const auto & first_pt = pts0[0];

		double x_min = first_pt.x(), y_min = first_pt.y();
		double x_max = first_pt.x(), y_max = first_pt.y();
		for (const auto & polygon : _polygons) {
			const std::vector<Point> & pts = polygon.points();
			for (const auto & pt : pts) {
				if (x_min > pt.x()) x_min = pt.x();
				if (y_min > pt.y()) y_min = pt.y();
				if (x_max < pt.x()) x_max = pt.x();
				if (y_max < pt.y()) y_max = pt.y();
			}
		}
		return Bounds {
			std::make_tuple(Pixel(int(round(x_min)), int(round(y_min)), 0),
			size_t(round(x_max - x_min)),
			size_t(round(y_max - y_min)))
		};
	}

	void Figure::fill_depth_buffer(DepthBuffer * z_buffer)	{
		for (auto & pol : _polygons)
			pol.fill_depth_buffer(z_buffer, _color);
	}
}