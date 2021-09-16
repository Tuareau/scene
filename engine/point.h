#pragma once

namespace tua {

	static const size_t POINT_SIZE = 4;

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
		Point(double x, double y, double z);
		Point(double x, double y, double z, double delta);
		~Point() = default;

		double x() const;
		double y() const;
		double z() const;
		double delta() const;

		Point & operator+(const Point & other);
		Point & operator*(double multiplier);
		double & operator[](size_t idx);
		double operator[](size_t idx) const;

		bool operator==(const Point & other);

		friend Point operator*(double multiplier, const Point & other);
	};

};