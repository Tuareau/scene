#pragma once

#include <algorithm>
#include <vector>
#include <cmath>

#include "axes.h"
#include "sides.h"
#include "polygon.h"
#include "point.h"

namespace tua {

	class Figure
	{
	protected:
		std::vector<Polygon> _polygons;

		Point average_point() const;

	public:
		Figure() = default;
		Figure(std::vector<Polygon> & polygons)
			: _polygons(polygons) {}
		~Figure() = default;

		//virtual void draw(Matrix * z_buffer) const = 0;
		//virtual void fill_depth_buffer(Matrix * z_buffer) const = 0;

		virtual void displace(Sides side, double step) = 0;
		virtual void scale(double coef) = 0;
		virtual void spin(Axes axis, double angle) = 0;
	};
}

