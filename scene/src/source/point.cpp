#include "point.h"

namespace tua {

	Point::Point() 
		: _x(0.0), _y(0.0), _z(0.0), _delta(1.0) {}
	Point::Point(double x, double y, double z, double delta) 
		: _x(x), _y(y), _z(z), _delta(delta) {}
	Point::Point(const Pixel & other) {
		_x = other.x();
		_y = other.y();
		_z = other.depth();
		_delta = 1.0;
	}

	double Point::x() const { return _x; }
	double Point::y() const { return _y; }
	double Point::z() const { return _z; }
	double Point::delta() const { return _delta; }

	double & Point::operator[](size_t idx) {
		switch (idx) {
		case 0:
			return _x; break;
		case 1:
			return _y; break;
		case 2:
			return _z; break;
		case 3:
			return _delta; break;
		default:
			throw "inv idx";
		}
	}

	double Point::operator[](size_t idx) const
	{
		switch (idx) {
		case 0:
			return _x; break;
		case 1:
			return _y; break;
		case 2:
			return _z; break;
		case 3:
			return _delta; break;
		default:
			throw "inv idx";
		}
	}

	bool Point::operator==(const Point & other) {
		return (_x == other._x) &&
			(_y == other._y) &&	(_z == other._z);
	}

	Point & tua::Point::operator=(const Pixel & other)
	{
		_x = other.x();
		_y = other.y();
		_z = other.depth();
		_delta = 1.0;
		return *this;
	}

	//bool Point::operator!=(const Point & other) {
	//	return !(*this == other);
	//}
};