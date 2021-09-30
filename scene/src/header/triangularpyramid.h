#pragma once

#include <vector>
#include <cmath>

#include "figure.h"
#include "polygon.h"

namespace tua {

	class TriangularPyramid : public Figure
	{
	private:
		void set_polygons_visibility() override;

	public:
		TriangularPyramid() = default;
		TriangularPyramid(std::vector<Polygon> & polygons);
		TriangularPyramid(Point base, size_t length);
		~TriangularPyramid() = default;

		//virtual void draw(Matrix * z_buffer) const override;
		//virtual void fill_depth_buffer(Matrix * z_buffer) const override;

		void draw() const;
	};
}