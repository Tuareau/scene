#include "bounds.h"

tua::Bounds::Bounds() {
	_base = Pixel();
	_size = { 0, 0 };
}

tua::Bounds::Bounds(const Pixel & base, size_t width, size_t height) {
	_base = base;
	_size = { width, height };
}

tua::Bounds::Bounds(const Bounds & other) {
	_base = other._base;
	_size = { other._size.width, other._size.height };
}

tua::Bounds & tua::Bounds::operator=(const Bounds & other) {
	_base = other._base;
	_size = { other._size.width, other._size.height };
	return *this;
}

std::tuple<tua::Pixel, size_t, size_t> tua::Bounds::as_touple() const {
	return std::make_tuple(_base, _size.width, _size.height);
}