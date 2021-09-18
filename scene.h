#pragma once

#include <vector>
#include <cmath>
#include <utility>

#include "figure.h"
#include "matrix.h"

#include "../graphics.h"

namespace tua {

	class Scene
	{
	private:
		std::vector<Figure *> _figures;
		// ZBuffer * _z_buffer;
		// KeyboardListener * keyboard_listener;
		std::tuple<double, double, double> _axes_angles;


		// window handling


	public:
		// add figure
		// draw figures
		// getkey
		// rotate axes
		// update buffer

	};

}