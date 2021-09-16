#pragma once

#include <vector>

#include "../graphics.h"

namespace tua {

	class Polygon
	{
	private:
		std::vector<Point> _points;
		bool is_visible;

	public:
		Polygon();
		Polygon(std::vector<Point> & points);
		~Polygon() = default;

		void draw() const;
	};

}