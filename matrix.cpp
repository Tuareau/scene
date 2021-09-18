#include "matrix.h"

namespace tua {

	Matrix::Matrix(const std::vector<Point> & points) {
		_points = points;
	}

	const Point & Matrix::operator[](size_t idx) const {
		return _points.at(idx);
	}

	Point & Matrix::operator[](size_t idx) {
		return _points.at(idx);
	}

	Matrix Matrix::operator*(const Matrix & other) {
		this->multiply(other);
		return *this;
	}

	void Matrix::operator*=(const Matrix & other) {
		multiply(other);
	}

	void Matrix::multiply(const Matrix & other)
	{
		if (other._points.size() > POINT_SIZE)
			throw std::invalid_argument("Matrix::operator*() - wrong matrix dimension, must be 4x4");
		Matrix result;
		for (size_t i = 0; i < _points.size(); ++i)
			result._points.emplace_back(0, 0, 0);
		for (size_t i = 0; i < _points.size(); ++i) {
			for (size_t j = 0; j < POINT_SIZE; ++j) {
				for (size_t k = 0; k < POINT_SIZE; ++k)
					result[i][j] = _points[i][k] * other._points[k][j];
			}
		}
		_points = result._points;
	}

	Matrix & Matrix::operator=(const Matrix & other)
	{
		if (this != &other)
			_points = other._points;
		return *this;
	}

	Matrix * make_shear_transform(double dx, double dy, double dz)
	{
		std::vector<Point> shear_points {
			Point(1, 0, 0, dx),
			Point(0, 1, 0, dy),
			Point(0, 0, 1, dz),
			Point(0, 0, 0, 1)
		};
		auto matrix_ptr = new Matrix(shear_points);
		return matrix_ptr;
	}

	void Matrix::shear(double dx, double dy, double dz) {
		Matrix * shear_transform = make_shear_transform(dx, dy, dz);
		multiply(*shear_transform);
	}

	Point Matrix::average_point() const
	{
		double aver_x = 0.0, aver_y = 0.0, aver_z = 0.0;
		for (auto point : _points) {
			aver_x += point.x();
			aver_y += point.y();
			aver_z += point.z();
		}
		aver_x /= _points.size();
		aver_x /= _points.size();
		aver_x /= _points.size();
		return Point(aver_x, aver_y, aver_z);
	}

	Matrix * make_scale_transform(const Point & base, double coef)
	{
		std::vector<Point> scale_points {
			Point(coef, 0, 0, base.x() * (1 - coef)),
			Point(0, coef, 0, base.y() * (1 - coef)),
			Point(0, 0, coef, base.z() * (1 - coef)),
			Point(0, 0, 0, 1),
		};
		Matrix * matrix_ptr = new Matrix(scale_points);
		return matrix_ptr;
	}

	void Matrix::scale(double coef) {
		Matrix * scale_transform = make_scale_transform(average_point(), coef);
		multiply(*scale_transform);
	}

	Matrix * make_rotate_x_transform(const Point & base, double radian)
	{
		auto cos_value = std::cos(radian), sin_value = std::sin(radian);
		std::vector<Point> rotate_points {
			Point(1, 0, 0, 0),
			Point(0, cos_value, -sin_value, base.y() * (1 - cos_value) + base.z() * sin_value),
			Point(0, sin_value, cos_value, base.z() * (1 - cos_value) - base.y() * sin_value),
			Point(0, 0, 0, 1)
		};
		auto matrix_ptr = new Matrix(rotate_points);
		return matrix_ptr;
	}

	Matrix * make_rotate_y_transform(const Point & base, double radian)
	{
		auto cos_value = std::cos(radian), sin_value = std::sin(radian);
		std::vector<Point> rotate_points {
			Point(cos_value, 0, sin_value, base.x() * (1 - cos_value) - base.z() * sin_value),
			Point(0, 1, 0, 0),
			Point(-sin_value, 0, cos_value, base.z() * (1 - cos_value) + base.x() * sin_value),
			Point(0, 0, 0, 1)
		};
		auto matrix_ptr = new Matrix(rotate_points);
		return matrix_ptr;
	}

	Matrix * make_rotate_z_transform(const Point & base, double radian)
	{
		auto cos_value = std::cos(radian), sin_value = std::sin(radian);
		std::vector<Point> rotate_points {
			Point(cos_value, -sin_value, 0, base.x() * (1 - cos_value) + base.y() * sin_value),
			Point(sin_value, cos_value, 0, base.y() * (1 - cos_value) - base.x() * sin_value),
			Point(0, 0, 1, 0),
			Point(0, 0, 0, 1)
		};
		auto matrix_ptr = new Matrix(rotate_points);
		return matrix_ptr;
	}

	void Matrix::rotate(double angle, Axes axis) {
		double rad = 3.14 / 180 * angle;
		Matrix * rotate_transform;
		switch (axis) {
			case Axes::X:
				rotate_transform = make_rotate_x_transform(average_point(), rad);
				multiply(*rotate_transform);
				break;
			case Axes::Y:
				rotate_transform = make_rotate_y_transform(average_point(), rad);
				multiply(*rotate_transform);
				break;
			case Axes::Z:
				rotate_transform = make_rotate_z_transform(average_point(), rad);
				multiply(*rotate_transform);
				break;
		}
	}

	Matrix * tua::make_coordinates_y_transform(bool is_inverse, double angle) {
		double rad = 3.14 / 180 * angle;
		auto cos_value = std::cos(rad), sin_value = std::sin(rad);
		if (is_inverse) 
			sin_value = -sin_value;
		std::vector<Point> coordinates_points {
			Point(cos_value, 0, -sin_value, 0),
			Point(0, 1, 0, 0),
			Point(sin_value, 0, cos_value, 0),
			Point(0, 0, 0, 1)
		};
		auto matrix_ptr = new Matrix(coordinates_points);
		return matrix_ptr;
	}

}