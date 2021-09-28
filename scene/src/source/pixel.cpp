#include "pixel.h"

namespace tua {

	Pixel::Pixel() 
		: _x(0), _y(0), _depth(0), _color(WHITE) {}

	Pixel::Pixel(int x, int y, int depth, int color) 
		: _x(x), _y(y), _depth(depth), _color(color) {}

	int Pixel::x() const { return _x; }

	int Pixel::y() const { return _y; }

	int Pixel::depth() const { return _depth; }

	int Pixel::color() const { return _color; }

	void Pixel::set_depth(int depth) { _depth = depth; }

	void Pixel::set_color(int color) { _color = color; }

	//bool Pixel::operator==(const Pixel & other) {
	//	return _x == other._x && _y == other._y;
	//}


}