#pragma once

#include <algorithm>
#include <vector>
#include <cmath>

#include "axes.h"
#include "sides.h"
#include "polygon.h"
#include "point.h"
#include "depthbuffer.h"

namespace tua {

	class Figure
	{
	private:
		virtual void set_polygons_visibility() = 0;

	protected:
		std::vector<Polygon> _polygons;

		Point average_point() const;

	public:
		Figure() = default;
		Figure(std::vector<Polygon> & polygons)
			: _polygons(polygons) {}
		~Figure() = default;

		//virtual void draw(DepthBuffer * z_buffer) const = 0;
		//virtual void fill_depth_buffer(DepthBuffer * z_buffer) const = 0;

		virtual void displace(Sides side, double step) = 0;
		virtual void scale(double coef) = 0;
		virtual void spin(Axes axis, double angle) = 0;

		virtual void draw() const = 0;
	};
}

