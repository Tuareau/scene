#pragma once

#include <vector>

#include "graphics.h"

#include "figure.h"
#include "color.h"

namespace tua {

	struct Depth {
		int z;
		Figure::FigureType object_type;
		Color color;
	};

	class Pixel
	{
	private:
		size_t _x;
		size_t _y;
		std::vector<Depth> _depths;

	public:
		Pixel() = delete;
		Pixel(const Pixel & other) = default;
		Pixel(size_t x, size_t y);
		~Pixel() = default;

		Pixel & operator=(const Pixel & other) = default;

		size_t x() const;
		size_t y() const;

		void push_depth(const Depth & depth);




	};

};