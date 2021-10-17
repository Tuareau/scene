#pragma once

#include "graphics.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <array>

#include "figure.h"
#include "depthbuffer.h"
#include "keyboardlistener.h"

#define MOVE_STEP 8.0
#define ANGLE_STEP 10.0
#define SCALE_STEP 0.1

//enum colors {
//	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
//	LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
//};

namespace tua {

	struct Parameters {
		double move_step;
		double angle_step;
		double scale_step;
	};

	class Scene
	{
	private:
		std::array<Figure *, Figure::FIGURES> _figures;
		Parameters _parameters;

		DepthBuffer * _buffer;
		KeyboardListener _keyboard_listener;

		enum class SceneState { STILL, CHANGED };
		SceneState _state = SceneState::STILL;

		void draw() const;
		void update_buffer();
		void show_instruction() const;

	public:
		Scene(const std::string & title, size_t width = 960, size_t height = 540);
		Scene(const Scene & scene) = delete;
		~Scene();

		void add_figure(Figure * figure);
		void remove_figure(Figure::FigureType type);
		//void rotate_axes();

		void run();
	};

}