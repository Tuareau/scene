#pragma once

#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <algorithm>
#include <vector>
#include <cmath>

#include "axes.h"
#include "sides.h"
#include "color.h"
#include "point.h"
#include "bounds.h"

namespace tua {

	class Polygon;
	class DepthBuffer;

	class Figure
	{
	protected:
		std::vector<Polygon> _polygons;
		Color _color;

		Point average_point() const;

	public:
		Figure() = default;
		Figure(std::vector<Polygon> & polygons, Color color);
		explicit Figure(Color color);
		virtual ~Figure() = default;

		void displace(Sides side, double step);
		void scale(double coef);
		void spin(Axes axis, double angle);

		Bounds bounds() const;
		Color color() const;
		void fill_depth_buffer(DepthBuffer * z_buffer);
		void clear_depth_buffer(DepthBuffer * z_buffer);

		static const size_t FIGURES = 2;
		enum class FigureType { PARALLELEPIPED, TRIANGULAR_PYRAMID, NONE };
		virtual FigureType type() const = 0;
	};

	class MovableFigure
	{
	public:
		enum class MoveState { STILL, MOVED };
	private:
		Figure * _figure;
		MoveState _state;
	public:
		MovableFigure() : _figure(nullptr), _state(MoveState::STILL) {}
		explicit MovableFigure(Figure * figure, MoveState state = MoveState::STILL)
			: _figure(figure), _state(state) {}
		MovableFigure(const MovableFigure & other) = default;

		bool exist() const { return _figure; }

		Figure * figure() { return _figure; }
		const Figure * figure() const { return _figure; }

		Figure::FigureType type() const { return _figure->type(); }
		Bounds bounds() const { return _figure->bounds(); }

		void change_state(MoveState state) { _state = state; }
		MoveState state() const { return _state; }
		void reset_state() { _state = MoveState::STILL; }
	};
}

#endif