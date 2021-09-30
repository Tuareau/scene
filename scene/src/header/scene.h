#pragma once

#include "graphics.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "figure.h"
#include "parallelepiped.h"
#include "triangularpyramid.h"
#include "depthbuffer.h"

#define ESC 27

//enum colors {
//	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
//	LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
//};

namespace tua {

	struct Parameters {
		double distance;
		double alpha;
		double scale;
	};

	class Scene
	{
	private:
		std::vector<Figure *> _figures;
		const static size_t _objects_max_count = 2;
		Parameters _parameters = { 8.0, 10.0, 0.1 };

		DepthBuffer * _buffer;

		void draw() const;
		void update_buffer();
		void show_instruction() const;

	public:
		Scene(const std::string & title, size_t width = 960, size_t height = 540);
		Scene(const Scene & scene) = delete;
		~Scene();

		void add_figure(Figure * figure);
		void set_objects_movement(double distance, double alpha, double scale);
		//void rotate_axes();

		void run();
	};

}