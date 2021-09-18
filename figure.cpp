#include "figure.h"

tua::Point tua::Figure::average_point() const
{	
	std::set<Point> unique_points;
	for (const auto & polygon : _polygons) {
		const auto & points = polygon.points();
		for (const auto & point : points)
			unique_points.insert(point);
	}
	return average_point_from_set(unique_points);
}

tua::Point tua::average_point_from_set(const std::set<Point>& points)
{
	double aver_x = 0.0, aver_y = 0.0, aver_z = 0.0;
	for (const auto & point : points) {
		aver_x += point.x();
		aver_y += point.y();
		aver_z += point.z();
	}
	aver_x /= points.size();
	aver_x /= points.size();
	aver_x /= points.size();
	return Point(aver_x, aver_y, aver_z);
}