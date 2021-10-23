#pragma once

#ifndef _PIXEL_H_
#define _PIXEL_H_

#include <vector>

#include "graphics.h"

#include "color.h"
#include "figure.h"

namespace tua {

	struct Depth {
		int z;
		typename Figure::FigureType object_type;
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
		const Depth & operator[](size_t idx) const;
		Depth & operator[](size_t idx);

		size_t x() const;
		size_t y() const;

		Color nearest_color() const;

		void push_depth(const Depth & depth);
		void erase_depths(Figure::FigureType type);

	};

};

#endif