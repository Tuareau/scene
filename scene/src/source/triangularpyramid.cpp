#include "triangularpyramid.h"

namespace tua {

	TriangularPyramid::TriangularPyramid(std::vector<Polygon> & polygons, int color)
		: Figure(polygons, color) {}

	TriangularPyramid::TriangularPyramid(Point base, size_t length, int color) 
		: Figure(color) {
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

	Figure::FigureType TriangularPyramid::type() const {
		return Figure::FigureType::TRIANGULAR_PYRAMID;
	}
}