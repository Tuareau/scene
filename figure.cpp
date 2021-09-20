#include "figure.h"

namespace tua {

	Point Figure::average_point() const
	{		
		std::vector<Point> points;
		for (const auto & polygon : _polygons) {
			const auto & pts = polygon.points();
			points.insert(points.end(), pts.begin(), pts.end());
		}

		auto less_point {
			[](const auto & lhs, const auto & rhs) {
				return (pow(lhs.x(), 2) + pow(lhs.y(), 2) + pow(lhs.z(), 2)) <
					(pow(rhs.x(), 2) + pow(rhs.y(), 2) + pow(rhs.z(), 2)); }
		};
		std::sort(points.begin(), points.end(), less_point);
		points.erase(std::unique(points.begin(), points.end()), points.end());

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
}