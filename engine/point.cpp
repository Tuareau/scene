#include "point.h"

namespace tua {

	Point::Point() 
		: _x(0), _y(0), _z(0), _delta(1) {}
	Point::Point(double x, double y, double z) 
		: _x(x), _y(y), _z(z), _delta(1.0) {}
	Point::Point(double x, double y, double z, double delta) 
		: _x(x), _y(y), _z(z), _delta(delta) {}

	double Point::x() const { return _x; }
	double Point::y() const { return _y; }
	double Point::z() const { return _z; }
	double Point::delta() const { return _delta; }

	Point & Point::operator+(const Point & other) {
		_x + other._x;
		_y + other._y;
		_z + other._z;
		_delta + other._delta;
		return *this;
	}

	Point & Point::operator*(double multiplier) {
		_x * multiplier;
		_y * multiplier;
		_z * multiplier;
		_delta * multiplier;
		return *this;
	}

	Point operator*(double multiplier, const Point & other) {
		return Point(other._x * multiplier,
			other._y * multiplier,
			other._z * multiplier,
			other._delta * multiplier);
	}

	double & Point::operator[](size_t idx) {
		switch (idx) {
		case 0:
			return _x;
		case 1:
			return _y;
		case 2:
			return _z;
		case 3:
			return _delta;
		default:
			throw "inv idx";
		}
	}

	double Point::operator[](size_t idx) const
	{
		switch (idx) {
		case 0:
			return _x;
		case 1:
			return _y;
		case 2:
			return _z;
		case 3:
			return _delta;
		default:
			throw "inv idx";
		}
	}

	bool tua::Point::operator==(const Point & other) {
		return (_x == other._x) && 
			(_y == other._y) && 
			(_z == other._z) && 
			(_delta == other._delta);
	}
};