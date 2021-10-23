#include "bounds.h"

tua::Bounds::Bounds() {
	_base = { 0, 0 };
	_size = { 0, 0 };
}

tua::Bounds::Bounds(const Vec2 & base, size_t width, size_t height) {
	_base = base;
	_size = { width, height };
}

tua::Bounds::Bounds(const Bounds & other) {
	_base = other._base;
	_size = { other._size.width, other._size.height };
}

tua::Bounds & tua::Bounds::operator=(const Bounds & other) {
	_base = other._base;
	_size = other._size;
	return *this;
}

std::tuple<tua::Vec2, size_t, size_t> tua::Bounds::as_touple() const {
	return std::make_tuple(_base, _size.width, _size.height);
}

bool tua::Bounds::empty() const {
	return _size.width == 0 && _size.height == 0;
}

tua::Bounds tua::make_bounds(const Vec2 & base, size_t width, size_t height) {
	return Bounds(base, width, height);
}