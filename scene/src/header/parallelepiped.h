#pragma once

#include <vector>

#include "figure.h"
#include "polygon.h"

namespace tua {

	class Parallelepiped : public Figure
	{
	private:
		void set_polygons_visibility() override;

	public:
		Parallelepiped() = default;
		Parallelepiped(std::vector<Polygon> & polygons);
		Parallelepiped(Point base, size_t height, size_t width, size_t depth);
		~Parallelepiped() = default;

		//virtual void draw(Matrix * z_buffer) const override;
		//virtual void fill_depth_buffer(Matrix * z_buffer) const override;

		void draw() const;
	};
}