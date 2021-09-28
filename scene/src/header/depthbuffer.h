#pragma once

#include <vector>
#include <climits>
#include <exception>

#include <iostream>

#include "graphics.h"
#include "pixel.h"

using std::vector;

namespace tua {

	struct Size {
		size_t width;
		size_t height;
	};

	class DepthBuffer
	{
	private:
		vector<vector<Pixel>> _screen_map;
		Size _size;
		int _base_color;

	public:
		DepthBuffer() = delete;
		DepthBuffer(const DepthBuffer & other) = delete;
		DepthBuffer(size_t width, size_t height, int base_color);
		~DepthBuffer() = default;

		Pixel & operator()(size_t x_idx, size_t y_idx);
		size_t width() const;
		size_t height() const;

		void clear();
		void draw(const Bounds & bounds) const;

		void SHOW_DEPTHS() const;
		void SHOW_COLORS() const;

	};

};
