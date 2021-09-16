#include "parallelepiped.h"

namespace tua {

	Parallelepiped::Parallelepiped(std::vector<Polygon>& polygons) 
		: Figure(polygons) {}

	void Parallelepiped::displace(Sides side, double step) {

	}

	void Parallelepiped::scale(double coef) {

	}

	void Parallelepiped::spin(Axes axis, double angle) {

	}

	void Parallelepiped::draw(Matrix * z_buffer) const {

	}

	void Parallelepiped::fill_depth_buffer(Matrix * z_buffer) const {

	}
}
