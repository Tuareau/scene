#pragma once

#include "graphics.h"

namespace tua {

	class Pixel
	{
	private:
		int _x;
		int _y;
		int _depth;
		int _color;

	public:
		Pixel();
		Pixel(const Pixel & other) = default;
		Pixel(int x, int y, int depth, int color = WHITE);
		~Pixel() = default;

		int x() const;
		int y() const;
		int depth() const;

		//bool operator==(const Pixel & other);
		//bool operator<(const Pixel & other);
		//bool operator!=(const Point & other);
	};

};