#include "bounds.h"

tua::Bounds::Bounds() {
	_base = { 0, 0 };
	_size = { 0, 0 };
	_state = State::UNSET;
}

tua::Bounds::Bounds(const Vec2 & base, size_t width, size_t height) {
	_base = { base.x - BOUND_ERROR, base.y - BOUND_ERROR };
	_size = { width + BOUND_ERROR, height + BOUND_ERROR };
	_state = State::SET;
}

tua::Bounds::Bounds(const Bounds & other) {
	_base = other._base;
	_size = { other._size.width, other._size.height };
	_state = other._state;
}

tua::Bounds & tua::Bounds::operator=(const Bounds & other) {
	_base = other._base;
	_size = other._size;
	_state = other._state;
	return *this;
}

std::tuple<tua::Vec2, size_t, size_t> tua::Bounds::as_touple() const {
	return std::make_tuple(_base, _size.width, _size.height);
}

bool tua::Bounds::empty() const {
	return _size.width == 0 && _size.height == 0;
}

bool tua::Bounds::is_set() const {
	return _state == State::SET;
}

tua::Bounds tua::make_bounds(const Vec2 & base, size_t width, size_t height) {
	return Bounds(base, width, height);
}

tua::Bounds tua::Bounds::compose(const Bounds & other) {
	auto base_x = std::min(this->_base.x, other._base.x);
	auto base_y = std::min(this->_base.y, other._base.y);

	auto this_end_x = this->_base.x + this->_size.width;
	auto other_end_x = other._base.x + other._size.width;
	auto end_x = std::max(this_end_x, other_end_x);

	auto this_end_y = this->_base.y + this->_size.height;
	auto other_end_y = other._base.y + other._size.height;
	auto end_y = std::max(this_end_y, other_end_y);

	auto width = end_x - base_x;
	auto height = end_y - base_y;

	Vec2 base = { base_x, base_y };
	return Bounds(base, width, height);
}