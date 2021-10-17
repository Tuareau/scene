#include "scene.h"

namespace tua {

	Scene::Scene(const std::string & title, size_t width, size_t height) {
		initwindow(width, height, title.c_str());
		_buffer = new DepthBuffer(width, height, BLACK);
		for (size_t i = 0; i < Figure::FIGURES; ++i) {
			_figures[i] = nullptr;
		}
		_parameters = { MOVE_STEP, ANGLE_STEP, SCALE_STEP };
	}

	void Scene::add_figure(Figure * figure) {
		const auto index = size_t(figure->type());
		if (index >= Figure::FIGURES) {
			throw std::logic_error("Scene::add_figure(): adding object is not allowed");
		}
		else if (!_figures[index]) {
			_figures[index] = figure;
		}
	}

	void Scene::remove_figure(Figure::FigureType type) {
		const auto index = size_t(type);
		if (index >= Figure::FIGURES) {
			throw std::logic_error("Scene::remove_figure(): removing object is not allowed");
		}
		else {
			delete _figures[index];
			_figures[index] = nullptr;
		}
	}

	Scene::~Scene() {
		delete _buffer;
		closegraph(ALL_WINDOWS);
	}

	void Scene::show_instruction() const {
		using std::cout;
		cout << std::setw(40) << "\nThe instruction of using\n";
		for (const auto & figure : _figures) {
			switch (figure->type()) {
			case Figure::FigureType::PARALLELEPIPED:
				cout << std::setw(40) << "\nPARALLELEPIPED\n";
				cout << std::setw(40) << "Move: A, S, D, W, R, T\n";
				cout << std::setw(40) << "Rotate: (Z, X), (C, V), (F, G)\n";
				cout << std::setw(40) << "Scale: Q, E\n";
				break;
			case Figure::FigureType::TRIANGULAR_PYRAMID:
				cout << std::setw(40) << "\nTRIANGULAR PYRAMID\n";
				cout << std::setw(40) << "Move: I, J, K, L, 9, 0\n";
				cout << std::setw(40) << "Rotate: (B, N), (M, P), (Y, H)\n";
				cout << std::setw(40) << "Scale: U, O\n";
				break;
			default:
				break;
			}
		}
		cout << std::setw(40) << "Press ESC to quit\n" << std::endl;
	}

	void Scene::draw() const {
		clearviewport();
		for (const auto & figure : _figures) {
			_buffer->draw(figure->bounds());
		}
	}

	void Scene::update_buffer() {
		_buffer->clear();
		for (const auto & figure : _figures) {
			figure->fill_depth_buffer(_buffer);
		}
	}

	void Scene::run() {
		show_instruction();
		const auto idx0 = size_t(Figure::FigureType::PARALLELEPIPED);
		const auto idx1 = size_t(Figure::FigureType::TRIANGULAR_PYRAMID);
		auto figure0 = _figures[idx0];
		auto figure1 = _figures[idx1];
		_state = SceneState::CHANGED;
		while (true) {
			if (_state == SceneState::CHANGED) {
				update_buffer();
				draw();
				_state = SceneState::STILL;
			}

			auto key = _keyboard_listener.get_active_key();
			if (key >= KeyboardListener::Key::A &&
				key < KeyboardListener::Key::NONE) {
				_state = SceneState::CHANGED;
			}
			if (figure0) {
				switch (key) {
				case KeyboardListener::Key::ESC:
					return;
					break;
				case KeyboardListener::Key::A:
					figure0->displace(Sides::LEFT, _parameters.move_step);
					break;
				case KeyboardListener::Key::S:
					figure0->displace(Sides::DOWN, _parameters.move_step);
					break;
				case KeyboardListener::Key::D:
					figure0->displace(Sides::RIGHT, _parameters.move_step);
					break;
				case KeyboardListener::Key::W:
					figure0->displace(Sides::UP, _parameters.move_step);
					break;

				case KeyboardListener::Key::Q:
					figure0->scale(1.0 - _parameters.scale_step);
					break;
				case KeyboardListener::Key::E:
					figure0->scale(1.0 + _parameters.scale_step);
					break;

				case KeyboardListener::Key::Z:
					figure0->spin(Axes::X, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::X:
					figure0->spin(Axes::X, _parameters.angle_step);
					break;
				case KeyboardListener::Key::C:
					figure0->spin(Axes::Y, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::V:
					figure0->spin(Axes::Y, _parameters.angle_step);
					break;
				case KeyboardListener::Key::F:
					figure0->spin(Axes::Z, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::G:
					figure0->spin(Axes::Z, _parameters.angle_step);
					break;

				case KeyboardListener::Key::R:
					figure0->displace(Sides::CLOSER, _parameters.move_step);
					break;
				case KeyboardListener::Key::T:
					figure0->displace(Sides::FURTHER, _parameters.move_step);
					break;
				case KeyboardListener::Key::NONE:
					break;
				default:
					break;
				}
			}

			if (figure1) {
				switch (key) {
				case KeyboardListener::Key::J:
					figure1->displace(Sides::LEFT, _parameters.move_step);
					break;
				case KeyboardListener::Key::K:
					figure1->displace(Sides::DOWN, _parameters.move_step);
					break;
				case KeyboardListener::Key::L:
					figure1->displace(Sides::RIGHT, _parameters.move_step);
					break;
				case KeyboardListener::Key::I:
					figure1->displace(Sides::UP, _parameters.move_step);
					break;

				case KeyboardListener::Key::U:
					figure1->scale(1.0 - _parameters.scale_step);
					break;
				case KeyboardListener::Key::O:
					figure1->scale(1.0 + _parameters.scale_step);
					break;

				case KeyboardListener::Key::B:
					figure1->spin(Axes::X, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::N:
					figure1->spin(Axes::X, _parameters.angle_step);
					break;
				case KeyboardListener::Key::M:
					figure1->spin(Axes::Y, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::P:
					figure1->spin(Axes::Y, _parameters.angle_step);
					break;
				case KeyboardListener::Key::Y:
					figure1->spin(Axes::Z, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::H:
					figure1->spin(Axes::Z, _parameters.angle_step);
					break;
				case KeyboardListener::Key::K9:
					figure1->displace(Sides::CLOSER, _parameters.move_step);
					break;
				case KeyboardListener::Key::K0:
					figure1->displace(Sides::FURTHER, _parameters.move_step);
					break;
				case KeyboardListener::Key::NONE:
					break;
				default:
					break;
				}				
			}
		}
	}
}