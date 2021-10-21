#include "pixel.h"

namespace tua {

	Pixel::Pixel(size_t x, size_t y)
		: _x(x), _y(y) {}

	size_t Pixel::x() const { return _x; }

	size_t Pixel::y() const { return _y; }




}