#pragma once

#include <vector>
#include <cmath>
#include <exception>
#include "point.h"
#include "axes.h"

namespace tua {

	class Matrix
	{
	private:
		std::vector<Point> _points;
		
		Point average_point() const;
		Point & operator[](size_t idx);

	public:
		Matrix() = default;
		Matrix(const std::vector<Point> & points);
		Matrix(const Matrix & other) = default;
		~Matrix() = default;

		Matrix operator*(const Matrix & other);
		void operator*=(const Matrix & other);
		Matrix & operator=(const Matrix & other);

		void shear(double dx, double dy, double dz);
		void rotate(double angle, Axes axis);
		void scale(double coef);

		void multiply(const Matrix & other);
		
		const Point operator[](size_t idx) const;
		size_t size() const;
	};

	Matrix * make_shear_transform(double dx, double dy, double dz);
	Matrix * make_scale_transform(const Point & base, double coef);
	Matrix * make_rotate_x_transform(const Point & base, double angle);
	Matrix * make_rotate_y_transform(const Point & base, double angle);
	Matrix * make_rotate_z_transform(const Point & base, double angle);

	// Matrix * make_coordinates_x_transform(double angle);
	Matrix * make_coordinates_y_transform(bool is_inverse, double angle);
	// Matrix * make_coordinates_z_transform(double angle);
}