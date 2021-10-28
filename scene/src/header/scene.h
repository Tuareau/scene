#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include "graphics.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <array>

#include "figure.h"
#include "depthbuffer.h"
#include "keyboardlistener.h"
#include "color.h"

#define MOVE_STEP 8.0
#define ANGLE_STEP 10.0
#define SCALE_STEP 0.1

namespace tua {

	struct MovementParameters {
		double move_step;
		double angle_step;
		double scale_step;
	};

	class Scene
	{
	private:
		using FiguresArray = std::array<MovableFigure, Figure::FIGURES>;
		FiguresArray _figures;
		MovementParameters _parameters;	

		DepthBuffer * _buffer;
		KeyboardListener _keyboard_listener;

		void update_buffer();
		KeyboardListener::ProcessStatus process_figure_movement(MovableFigure & figure);

		void show_instruction() const;	

	public:
		Scene(const std::string & title, size_t width = 960, size_t height = 540);
		Scene(const Scene & scene) = delete;
		~Scene();

		void add_figure(Figure * figure);
		void remove_figure(Figure::FigureType type);

		void rotate_axes(Axes axis, double angle);

		void turn_light_on();

		void run();
	};
}

#endif