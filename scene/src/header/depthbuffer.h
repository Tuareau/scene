#pragma once

#include <vector>
#include <climits>
#include <exception>

#include <iostream>

#include "graphics.h"
#include "pixel.h"
#include "bounds.h"

using std::vector;

namespace tua {

	struct Size {
		size_t width;
		size_t height;
	};

	class DepthBuffer
	{
	private:
		vector<vector<Pixel>> _buffer;
		vector<Bounds> _used_bounds;
		Size _size;
		int _base_color;

		Bounds transform_bound(const Bounds & bound);
		void add_bound(const Bounds & bound);

	public:
		DepthBuffer() = delete;
		DepthBuffer(const DepthBuffer & other) = delete;
		DepthBuffer(size_t width, size_t height, int base_color);
		~DepthBuffer() = default;

		Pixel & operator()(size_t x_idx, size_t y_idx);
		size_t width() const;
		size_t height() const;

		void clear();
		void draw(const Bounds & bound);

	};

};
