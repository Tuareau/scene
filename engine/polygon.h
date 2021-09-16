#pragma once

#include <vector>
#include <iterator>

#include "point.h"

#include "../graphics.h"

namespace tua {

	class Polygon
	{
	private:
		std::vector<Point *> _points;
		bool _is_visible;

	public:
		Polygon();
		Polygon(std::vector<Point *> & points);
		Polygon(const Polygon & other);
		~Polygon();

		// double depth() const;
		void draw() const;

		size_t size() const;
		Point * operator[](size_t idx);
	};

	template<typename... Points>
	Polygon make_polygon(Points... point);
}