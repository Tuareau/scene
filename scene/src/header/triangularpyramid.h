#pragma once

#include <vector>
#include <cmath>

#include "figure.h"
#include "polygon.h"

namespace tua {

	class TriangularPyramid : public Figure
	{
	public:
		TriangularPyramid() = default;
		TriangularPyramid(std::vector<Polygon> & polygons, int color);
		TriangularPyramid(Point base, size_t length, int color);
		~TriangularPyramid() = default;
	};
}