#include "figure.h"
#include "bounds.h"
#include "depthbuffer.h"
#include "polygon.h"

namespace tua {

	Figure::Figure(std::vector<Polygon> & polygons, Color color)
		: _polygons(polygons), _color(color) {}

	Figure::Figure(Color color) : _color(color) {}

	Color Figure::color() const {
		return _color;
	}

	Point Figure::average_point() const {		
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
		for (auto & pol : _polygons) {
			pol.displace(side, step);
		}
	}

	void Figure::scale(double coef) {
		for (auto & pol : _polygons) {
			pol.scale(coef, Figure::average_point());
		}
	}

	void Figure::spin(Axes axis, double angle) {
		for (auto & pol : _polygons) {
			pol.spin(axis, angle, Figure::average_point());
		}
	}

	Bounds Figure::bounds() const {		
		using std::round;
		const auto & pts0 = _polygons[0].points();
		const auto & first_pt = pts0[0];

		double x_min = first_pt.x(), y_min = first_pt.y();
		double x_max = first_pt.x(), y_max = first_pt.y();
		for (const auto & polygon : _polygons) {
			const auto & pts = polygon.points();
			for (const auto & pt : pts) {
				if (x_min > pt.x()) x_min = pt.x();
				if (y_min > pt.y()) y_min = pt.y();
				if (x_max < pt.x()) x_max = pt.x();
				if (y_max < pt.y()) y_max = pt.y();
			}
		}
		auto width = static_cast<int>(round(x_max - x_min));
		auto height = static_cast<int>(round(y_max - y_min));
		Vec2 base = { 
			static_cast<int>(round(x_min)), 
			static_cast<int>(round(y_min)),
		};
		return Bounds(base, width, height);
	}

	void Figure::fill_depth_buffer(DepthBuffer * z_buffer) {
		for (auto & pol : _polygons) {
			pol.fill_depth_buffer(z_buffer);
		}
	}

	void Figure::clear_depth_buffer(DepthBuffer * z_buffer) {
		for (auto & pol : _polygons) {
			pol.clear_depth_buffer(z_buffer);
		}
	}
}