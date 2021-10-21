#pragma once

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

	struct Parameters {
		double move_step;
		double angle_step;
		double scale_step;
	};

	class Scene
	{
	private:
		using FiguresArray = std::array<MovableFigure, Figure::FIGURES>;
		FiguresArray _figures;
		Parameters _parameters;

		DepthBuffer * _buffer;
		KeyboardListener _keyboard_listener;

		void draw_buffer() const;
		void update_buffer();
		void apply_changes();
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

	class MovableFigure
	{
	public:
		enum class MoveState { STILL, MOVED };
	private:
		Figure * _figure;
		MoveState _state;
	public:
		MovableFigure() : _figure(nullptr), _state(MoveState::STILL) {}
		explicit MovableFigure(Figure * figure, MoveState state = MoveState::STILL) 
			: _figure(figure), _state(state) {}
		MovableFigure(const MovableFigure & other) = default;

		bool exist() const { return !_figure; }

		Figure * figure() { return _figure; }
		const Figure * figure() const { return _figure; }

		Figure::FigureType type() const { return _figure->type(); }

		void change_state(MoveState state) { _state = state; }
		MoveState state() const { return _state; }
		void reset_state() { _state = MoveState::STILL; }
	};

}