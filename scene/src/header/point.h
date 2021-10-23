#pragma once

#ifndef _POINT_H_
#define _POINT_H_

#include <stdexcept>

namespace tua {

	class Point
	{
	private:
		double _x;
		double _y;
		double _z;
		double _delta;

	public:
		Point();
		Point(const Point & other) = default;
		Point(double x, double y, double z, double delta = 1.0);
		~Point() = default;

		Point & operator=(const Point & other) = default;
		
		static const size_t POINT_SIZE = 4;

		double x() const;
		double y() const;
		double z() const;
		double delta() const;

		double & operator[](size_t idx);
		double operator[](size_t idx) const;

		bool operator==(const Point & other);
		bool operator!=(const Point & other);
	};

};

#endif