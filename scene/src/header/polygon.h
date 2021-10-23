#pragma once

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>
#include <cmath>

#include "graphics.h"

#include "axes.h"
#include "sides.h"
#include "color.h"
#include "matrix.h"
#include "figure.h"

namespace tua {

	class DepthBuffer;
	class Pixel;

	class Polygon
	{
	private:
		Matrix * _polygon_matrix;
		Figure::FigureType _figure_type;
		Color _filling_color;

		enum class PolygonPointsCount { ONE = 1, TWO, THREE, FOUR, NONE };
		PolygonPointsCount _points_count;

		std::vector<Pixel> collect_pixels(const Point & p1, const Point & p2) const;
		void paint_pixels(std::vector<Pixel> & pixels, Color color);
		void identify_pixels_with_figure(std::vector<Pixel> & pixels);


		void fill_line(DepthBuffer * z_buffer, const std::vector<Pixel> & pixels);
		using PolygonArea = std::pair<Point, std::vector<Pixel>>;
		void fill_area(DepthBuffer * z_buffer, PolygonArea area);
		void fill_edges(DepthBuffer * z_buffer, Color color = Color::WHITE);

	public:
		Polygon();
		Polygon(const std::vector<Point> & points, Figure::FigureType type, Color color);
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

		void fill_depth_buffer(DepthBuffer * z_buffer);
		void clear_depth_buffer(DepthBuffer * z_buffer);
	};

	template<typename... Points>
	Polygon make_polygon(Points... point) {
		std::vector<Point> points;
		points.push_back(point)...;
		return Polygon(points);
	}
}

#endif