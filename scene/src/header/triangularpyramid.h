#pragma once

#include <vector>
#include <cmath>

#include "color.h"
#include "figure.h"

namespace tua {

	class Polygon;

	class TriangularPyramid : public Figure
	{
	public:
		TriangularPyramid() = default;
		TriangularPyramid(Point base, size_t length, Color color);
		~TriangularPyramid() = default;

		Figure::FigureType type() const override;
	};
}