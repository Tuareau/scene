#pragma once

#include <vector>

#include "color.h"
#include "figure.h"

namespace tua {

	class Polygon;

	class Parallelepiped : public Figure
	{
	public:
		Parallelepiped() = default;
		Parallelepiped(std::vector<Polygon> & polygons, Color color);
		Parallelepiped(Point base, size_t width, size_t height, size_t depth, Color color);
		~Parallelepiped() = default;

		Figure::FigureType type() const override;
	};
}