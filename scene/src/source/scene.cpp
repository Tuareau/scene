#include "scene.h"

namespace tua {

	Scene::Scene(const std::string & title, size_t width, size_t height) {
		initwindow(width, height, title.c_str());
		_buffer = new DepthBuffer(width, height, Color::BLACK);
		_parameters = { MOVE_STEP, ANGLE_STEP, SCALE_STEP };
		for (auto & figure : _figures) {
			figure = MovableFigure(nullptr);
		}
	}

	void Scene::add_figure(Figure * figure) {
		const auto index = static_cast<size_t>(figure->type());
		if (index >= Figure::FIGURES) {
			throw std::logic_error("Scene::add_figure(): adding object is not allowed");
		}
		else if (_figures[index].exist()) {
			std::cout << "\nYou tried to add figure that already was added\n";			
		}
		else {
			_figures[index] = MovableFigure(figure);
		}
	}

	void Scene::remove_figure(Figure::FigureType type) {
		const auto index = static_cast<size_t>(type);
		if (index >= Figure::FIGURES) {
			throw std::logic_error("Scene::remove_figure(): removing object is not allowed");
		}
		else {
			delete _figures[index].figure();
			_figures[index] = MovableFigure(nullptr);
		}
	}

	Scene::~Scene() {
		delete _buffer;
		closegraph(ALL_WINDOWS);
	}

	void Scene::show_instruction() const {
		using std::cout;
		const auto indent { std::setw(40) };
		cout << indent << "\nThe instruction of using\n";
		for (const auto & figure : _figures) {
			if (figure.exist()) {
				switch (figure.figure()->type()) {
				case Figure::FigureType::PARALLELEPIPED:
					cout << indent << "\nPARALLELEPIPED\n";
					cout << indent << "Move: A, S, D, W, R, T\n";
					cout << indent << "Rotate: (Z, X), (C, V), (F, G)\n";
					cout << indent << "Scale: Q, E\n";
					break;
				case Figure::FigureType::TRIANGULAR_PYRAMID:
					cout << indent << "\nTRIANGULAR PYRAMID\n";
					cout << indent << "Move: I, J, K, L, 9, 0\n";
					cout << indent << "Rotate: (N, M), (7, 8), (Y, H)\n";
					cout << indent << "Scale: U, O\n";
					break;
				default:
					break;
				}
			}
		}
		cout << indent << "Press ESC to quit\n" << std::endl;
	}

	void Scene::update_buffer() {
		for (auto & figure : _figures) {
			if (figure.exist()) {
				if (figure.state() == MovableFigure::MoveState::MOVED) {
					_buffer->clear_figure(figure);
					_buffer->draw_figure(figure);
					figure.reset_state();
				}
			}
		}
	}

	void Scene::run() {
		show_instruction();
		for (auto & figure : _figures) {
			if (figure.exist()) {
				_buffer->draw_figure(figure);
			}
		}
		while (true) {			
			for (auto & figure : _figures) {
				auto process_status = process_figure_movement(figure);
				if (process_status == KeyboardListener::ProcessStatus::QUIT) {
					return;
				}
			}
			update_buffer();
		}
	}

	KeyboardListener::ProcessStatus Scene::process_figure_movement(MovableFigure & figure) {
		auto process_status = KeyboardListener::ProcessStatus::ACTION_MISSED;
		if (figure.exist()) {
			process_status = _keyboard_listener.process_actions(figure.figure(), _parameters);
			if (process_status == KeyboardListener::ProcessStatus::ACTION_DONE) {
				figure.change_state(MovableFigure::MoveState::MOVED);
			}
		}
		return process_status;
	}

}
