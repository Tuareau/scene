#pragma once

#include <algorithm>
#include <vector>
#include <cmath>

#include "axes.h"
#include "sides.h"
#include "polygon.h"
#include "point.h"
#include "pixel.h"
#include "depthbuffer.h"

namespace tua {

	class Figure
	{
	protected:
		std::vector<Polygon> _polygons;
		int _color;

		Point average_point() const;

	public:
		Figure() = default;
		Figure(std::vector<Polygon> & polygons, int color);
		explicit Figure(int color);
		~Figure() = default;

		void displace(Sides side, double step);
		void scale(double coef);
		void spin(Axes axis, double angle);

		Bounds bounds() const;
		void fill_depth_buffer(DepthBuffer * z_buffer);
	};
}

