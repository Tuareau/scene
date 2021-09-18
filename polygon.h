#pragma once

#include <vector>
#include <cmath>

#include "axes.h"
#include "sides.h"
#include "matrix.h"
#include "graphics.h"

namespace tua {

	class Polygon
	{
	private:
		Matrix * _polygon_matrix;
		bool _is_visible;

	public:
		Polygon();
		Polygon(std::vector<Point> & points);
		Polygon(const Polygon & other);
		~Polygon();

		// double depth() const;
		void draw() const;

		void displace(Sides side, double step);
		void scale(double coef);
		void spin(Axes axis, double angle);
	};

	template<typename... Points>
	Polygon make_polygon(Points... point);
}