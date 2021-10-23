#pragma once

#ifndef _DEPTHBUFFER_H_
#define _DEPTHBUFFER_H_

#include <vector>
#include <limits>
#include <exception>
#include <array>
#include <tuple>

#include <iostream>

#include "figure.h"
#include "graphics.h"
#include "pixel.h"
#include "size.h"
#include "color.h"

using std::vector;
using std::array;

namespace tua {

	class Bounds;

	class DepthBuffer
	{
	private:
		vector<vector<Pixel>> _buffer;
		array<Bounds, Figure::FIGURES> _active_bounds;
		Size _size;
		Color _base_color;

		void draw_bounds(const Bounds & bound) const;
		Bounds transform_figure_bounds(const Bounds & bound);

	public:
		DepthBuffer() = delete;
		DepthBuffer(const DepthBuffer & other) = delete;
		DepthBuffer(size_t width, size_t height, Color base_color);
		~DepthBuffer() = default;

		Pixel & operator()(size_t x_idx, size_t y_idx);
		size_t width() const;
		size_t height() const;

		void clear_figure(MovableFigure & figure);
		void draw_figure(MovableFigure & figure);

	};

	size_t to_index(Figure::FigureType type);

};

#endif