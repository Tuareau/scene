#pragma once

#include <vector>
#include <climits>
#include <exception>
#include <map>

#include <iostream>

#include "graphics.h"
#include "pixel.h"
#include "bounds.h"
#include "figure.h"

using std::vector;
using std::map;

namespace tua {

	struct Size {
		size_t width;
		size_t height;
	};

	class DepthBuffer
	{
	private:
		using MarkedBounds = std::pair<Figure::FigureType, Bounds>;

		vector<vector<Pixel>> _buffer;
		map<size_t, MarkedBounds> _active_bounds;
		Size _size;
		int _base_color;

		MarkedBounds transform_figure_bounds(const Bounds & bound, Figure::FigureType type);
		void add_marked_bounds(const MarkedBounds & marked_bound, Figure::FigureType type);

	public:
		DepthBuffer() = delete;
		DepthBuffer(const DepthBuffer & other) = delete;
		DepthBuffer(size_t width, size_t height, int base_color);
		~DepthBuffer() = default;

		Pixel & operator()(size_t x_idx, size_t y_idx);
		size_t width() const;
		size_t height() const;

		void clear();
		void draw_figure(const Figure * figure);

	};

};
