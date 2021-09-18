#pragma once

#include <vector>
#include <cmath>
#include <utility>

#include "figure.h"
#include "matrix.h"

#include "graphics.h"

#include <iostream>
#include <cctype>

#include "parallelepiped.h"
#include "point.h"

#define TUA_ESC 27
#define TUA_DIST 0.1 // смещение
#define TUA_ALPHA 0.1 // угол
#define TUA_INC 1.01 // коэф. для увеличения
#define TUA_DEC 0.99 // коэф. для уменьшения

namespace tua {

	class Scene
	{
	private:
		//std::vector<Figure *> _figures;
		// ZBuffer * _z_buffer;
		// KeyboardListener * keyboard_listener;
		//std::tuple<double, double, double> _axes_angles;
		// window handling


	public:
		Scene() = default;
		~Scene() = default;
		// add figure
		// draw figures
		// getkey
		// rotate axes
		// update buffer
		void run() const;
	};

}