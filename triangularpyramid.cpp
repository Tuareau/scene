#include "triangularpyramid.h"

namespace tua {

	TriangularPyramid::TriangularPyramid(std::vector<Polygon> & polygons)
		: Figure(polygons) {}

	TriangularPyramid::TriangularPyramid(Point base, size_t length) {
		const auto half_length = length / 2;
		const auto height = std::sqrt(std::pow(length, 2) - std::pow(half_length, 2));
		const auto inner_radius = std::sqrt(3) / 6 * length;

		Point pt0(base);
		Point pt1(base.x() - half_length, base.y() + height, base.z() + inner_radius);
		Point pt2(base.x() + half_length, base.y() + height, base.z() + inner_radius);
		Point pt3(base.x(), base.y() + height, base.z() - 2 * inner_radius);

		std::vector<Point> pts0 = { pt0, pt1, pt2 };
		std::vector<Point> pts1 = { pt0, pt2, pt3 };
		std::vector<Point> pts2 = { pt0, pt1, pt3 };
		std::vector<Point> pts3 = { pt1, pt2, pt3 };

		_polygons.emplace_back(pts0);
		_polygons.emplace_back(pts1);
		_polygons.emplace_back(pts2);
		_polygons.emplace_back(pts3);
	}

	void TriangularPyramid::set_polygons_visibility() {
		//auto less_aver_point_depth{
		//	[](const auto & polygon0, const auto & polygon1) {
		//		return polygon0.average_point().z() < polygon1.average_point().z();
		//	}
		//};
		//std::sort(_polygons.begin(), _polygons.end(), less_aver_point_depth);
		//const auto half = _polygons.size() / 2;
		//for (size_t i = 0; i < _polygons.size(); ++i) {
		//	if (i < half)
		//		_polygons[i].set_visibility(false);
		//	else
		//		_polygons[i].set_visibility(true);
		//}
	}

	void TriangularPyramid::draw() const {
		for (const auto & pol : _polygons)
			pol.draw();
	}

}