#pragma once

#include <vector>

#include "figure.h"
#include "polygon.h"

namespace tua {

	class Parallelepiped : public Figure
	{
	public:
		Parallelepiped() = default;
		Parallelepiped(std::vector<Polygon> & polygons);
		~Parallelepiped() = default;

		virtual void draw(Matrix * z_buffer) const override;
		virtual void fill_depth_buffer(Matrix * z_buffer) const override;

		virtual void displace(Sides side, double step) override;
		virtual void scale(double coef) override;
		virtual void spin(Axes axis, double angle) override;
	};

}