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
		Polygon(const std::vector<Point> & points);
		Polygon(const Polygon & other);
		Polygon(Polygon && other);
		~Polygon();

		Polygon & operator=(const Polygon & other);
		Polygon & operator=(Polygon && other);

		// double depth() const;
		void draw() const;

		void displace(Sides side, double step);
		void scale(double coef, const Point & base);
		void spin(Axes axis, double angle, const Point & base);

		Point average_point() const;
		const std::vector<Point> & points() const;
		void set_visibility(bool visible);
	};

	template<typename... Points>
	Polygon make_polygon(Points... point) {
		std::vector<Point> points;
		points.push_back(point)...;
		return Polygon(points);
	}
}