#pragma once

#include <vector>
#include <cmath>

#include "axes.h"
#include "sides.h"
#include "matrix.h"
#include "depthbuffer.h"
#include "graphics.h"
#include "pixel.h"

namespace tua {

	class Polygon
	{
	private:
		Matrix * _polygon_matrix;

		std::vector<Pixel> collect_pixels(const Point & p1, const Point & p2) const;
		void fill_pixels(DepthBuffer * z_buffer, const std::vector<Pixel> & pixels, int color);
		void fill_edges(DepthBuffer * z_buffer, int color = WHITE);

	public:
		Polygon();
		Polygon(const std::vector<Point> & points);
		Polygon(const Polygon & other);
		Polygon(Polygon && other) noexcept;
		~Polygon();

		Polygon & operator=(const Polygon & other);
		Polygon & operator=(Polygon && other) noexcept;

		void displace(Sides side, double step);
		void scale(double coef, const Point & base);
		void spin(Axes axis, double angle, const Point & base);

		Point average_point() const;
		const std::vector<Point> & points() const;

		void fill_depth_buffer(DepthBuffer * z_buffer, int color);

	};

	template<typename... Points>
	Polygon make_polygon(Points... point) {
		std::vector<Point> points;
		points.push_back(point)...;
		return Polygon(points);
	}
}