#pragma once

#include <vector>

#include "figure.h"
#include "polygon.h"

namespace tua {

	class Parallelepiped : public Figure
	{
	public:
		Parallelepiped() = default;
		Parallelepiped(std::vector<Polygon> & polygons, int color);
		Parallelepiped(Point base, size_t width, size_t height, size_t depth, int color);
		~Parallelepiped() = default;
	};
}