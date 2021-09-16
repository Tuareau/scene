#pragma once

#include <vector>
#include <set>

#include "axes.h"
#include "sides.h"
#include "matrix.h"
#include "polygon.h"

namespace tua {

	class Figure
	{
	protected:
		std::vector<Polygon> _polygons;
		Matrix * _figure_matrix;

		void fill_matrix();
		void sync_polygons();

	public:
		Figure() = default;
		Figure(std::vector<Polygon> & polygons)
			: _polygons(polygons) {}
		~Figure();

		virtual void draw(Matrix * z_buffer) const = 0;
		virtual void fill_depth_buffer(Matrix * z_buffer) const = 0;

		virtual void displace(Sides side, double step) = 0;
		virtual void scale(double coef) = 0;
		virtual void spin(Axes axis, double angle) = 0;
	};

	void Figure::fill_matrix()
	{
		std::set<Point *> figure_points;
		for (auto & polygon : _polygons) {
			for (size_t i = 0; i < polygon.size(); ++i)
				figure_points.insert(polygon[i]);
		}
		std::vector<Point> points;
		for (const auto & pt : figure_points)
			points.push_back(*pt);
		_figure_matrix = new Matrix(points);
	}

	inline Figure::~Figure() {
		delete _figure_matrix;
	}
}

