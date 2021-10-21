#include "scene.h"

namespace tua {

	Scene::Scene(const std::string & title, size_t width, size_t height) {
		initwindow(width, height, title.c_str());
		_buffer = new DepthBuffer(width, height, Color::BLACK);
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
		const auto indent { std::setw(40) };
		cout << indent << "\nThe instruction of using\n";
		for (const auto & figure : _figures) {
			switch (figure->type()) {
			case Figure::FigureType::PARALLELEPIPED:
				cout << indent << "\nPARALLELEPIPED\n";
				cout << indent << "Move: A, S, D, W, R, T\n";
				cout << indent << "Rotate: (Z, X), (C, V), (F, G)\n";
				cout << indent << "Scale: Q, E\n";
				break;
			case Figure::FigureType::TRIANGULAR_PYRAMID:
				cout << indent << "\nTRIANGULAR PYRAMID\n";
				cout << indent << "Move: I, J, K, L, 9, 0\n";
				cout << indent << "Rotate: (B, N), (M, P), (Y, H)\n";
				cout << indent << "Scale: U, O\n";
				break;
			default:
				break;
			}
		}
		cout << indent << "Press ESC to quit\n" << std::endl;
	}

	void Scene::draw_buffer() const {
		clearviewport();
		for (const auto * figure : _figures) {
			_buffer->draw_figure(figure);
		}
	}

	void Scene::update_buffer() {
		_buffer->clear();
		for (const auto & figure : _figures) {
			figure->fill_depth_buffer(_buffer);
		}
	}

	Figure * Scene::find_figure(Figure::FigureType type) {
		const auto idx = static_cast<size_t>(type);
		if (idx >= Figure::FIGURES) {
			return nullptr;
		}
		else {
			return _figures[idx];
		}
	}

	void Scene::run() {
		show_instruction();
		auto parallelepiped = find_figure(Figure::FigureType::PARALLELEPIPED);
		auto pyramid = find_figure(Figure::FigureType::TRIANGULAR_PYRAMID);
		_state = SceneState::CHANGED;
		while (true) {
			if (_state == SceneState::CHANGED) {
				update_buffer();
				draw_buffer();
				_state = SceneState::STILL;
			}

			auto key = _keyboard_listener.get_active_key();
			if (key >= KeyboardListener::Key::A &&
				key < KeyboardListener::Key::NONE) {
				_state = SceneState::CHANGED;
			}
			if (parallelepiped) {
				switch (key) {
				case KeyboardListener::Key::ESC:
					return;
					break;
				case KeyboardListener::Key::A:
					parallelepiped->displace(Sides::LEFT, _parameters.move_step);
					break;
				case KeyboardListener::Key::S:
					parallelepiped->displace(Sides::DOWN, _parameters.move_step);
					break;
				case KeyboardListener::Key::D:
					parallelepiped->displace(Sides::RIGHT, _parameters.move_step);
					break;
				case KeyboardListener::Key::W:
					parallelepiped->displace(Sides::UP, _parameters.move_step);
					break;

				case KeyboardListener::Key::Q:
					parallelepiped->scale(1.0 - _parameters.scale_step);
					break;
				case KeyboardListener::Key::E:
					parallelepiped->scale(1.0 + _parameters.scale_step);
					break;

				case KeyboardListener::Key::Z:
					parallelepiped->spin(Axes::X, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::X:
					parallelepiped->spin(Axes::X, _parameters.angle_step);
					break;
				case KeyboardListener::Key::C:
					parallelepiped->spin(Axes::Y, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::V:
					parallelepiped->spin(Axes::Y, _parameters.angle_step);
					break;
				case KeyboardListener::Key::F:
					parallelepiped->spin(Axes::Z, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::G:
					parallelepiped->spin(Axes::Z, _parameters.angle_step);
					break;

				case KeyboardListener::Key::R:
					parallelepiped->displace(Sides::CLOSER, _parameters.move_step);
					break;
				case KeyboardListener::Key::T:
					parallelepiped->displace(Sides::FURTHER, _parameters.move_step);
					break;
				case KeyboardListener::Key::NONE:
					break;
				default:
					break;
				}
			}

			if (pyramid) {
				switch (key) {
				case KeyboardListener::Key::J:
					pyramid->displace(Sides::LEFT, _parameters.move_step);
					break;
				case KeyboardListener::Key::K:
					pyramid->displace(Sides::DOWN, _parameters.move_step);
					break;
				case KeyboardListener::Key::L:
					pyramid->displace(Sides::RIGHT, _parameters.move_step);
					break;
				case KeyboardListener::Key::I:
					pyramid->displace(Sides::UP, _parameters.move_step);
					break;

				case KeyboardListener::Key::U:
					pyramid->scale(1.0 - _parameters.scale_step);
					break;
				case KeyboardListener::Key::O:
					pyramid->scale(1.0 + _parameters.scale_step);
					break;

				case KeyboardListener::Key::B:
					pyramid->spin(Axes::X, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::N:
					pyramid->spin(Axes::X, _parameters.angle_step);
					break;
				case KeyboardListener::Key::M:
					pyramid->spin(Axes::Y, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::P:
					pyramid->spin(Axes::Y, _parameters.angle_step);
					break;
				case KeyboardListener::Key::Y:
					pyramid->spin(Axes::Z, -_parameters.angle_step);
					break;
				case KeyboardListener::Key::H:
					pyramid->spin(Axes::Z, _parameters.angle_step);
					break;
				case KeyboardListener::Key::K9:
					pyramid->displace(Sides::CLOSER, _parameters.move_step);
					break;
				case KeyboardListener::Key::K0:
					pyramid->displace(Sides::FURTHER, _parameters.move_step);
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