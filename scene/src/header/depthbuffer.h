#pragma once

#include <vector>
#include <limits>
#include <exception>
#include <array>
#include <tuple>

#include <iostream>

#include "graphics.h"
#include "pixel.h"
#include "size.h"
#include "color.h"
#include "bounds.h"
#include "figure.h"

using std::vector;
using std::array;

namespace tua {

	class DepthBuffer
	{
	private:
		using MarkedBounds = std::pair<Figure::FigureType, Bounds>;

		vector<vector<Pixel>> _buffer;
		array<MarkedBounds, Figure::FIGURES> _active_bounds;
		Size _size;
		Color _base_color;

		MarkedBounds transform_figure_bounds(const Bounds & bound, Figure::FigureType type);
		void add_marked_bounds(const MarkedBounds & marked_bound, Figure::FigureType type);
		void draw_bound(Figure::FigureType type) const;

	public:
		DepthBuffer() = delete;
		DepthBuffer(const DepthBuffer & other) = delete;
		DepthBuffer(size_t width, size_t height, Color base_color);
		~DepthBuffer() = default;

		Pixel & operator()(size_t x_idx, size_t y_idx);
		size_t width() const;
		size_t height() const;

		void clear();
		void draw_figure(const Figure * figure);

	};

	size_t to_index(Figure::FigureType type) {
		return static_cast<size_t>(type);
	}

};
