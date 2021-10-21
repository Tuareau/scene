#include "scene.h"

namespace tua {

	Scene::Scene(const std::string & title, size_t width, size_t height) {
		initwindow(width, height, title.c_str());
		_buffer = new DepthBuffer(width, height, Color::BLACK);
		_parameters = { MOVE_STEP, ANGLE_STEP, SCALE_STEP };
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
		for (const auto & figure : _figures) {
			_buffer->draw_figure(figure.figure());
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
		while (true) {
			update_buffer();
			draw_buffer();
			apply_changes();
		}
	}

	void Scene::apply_changes() {
		auto par_iter = std::find_if(_figures.begin(), _figures.end(),
			[](const auto & figure) { 
				return figure.type() == Figure::FigureType::PARALLELEPIPED;
			});
		auto pyr_iter = std::find_if(_figures.begin(), _figures.end(),
			[](const auto & figure) {
				return figure.type() == Figure::FigureType::TRIANGULAR_PYRAMID;
			});

		auto parallelepiped = (par_iter != _figures.end()) ? 
			*par_iter : MovableFigure(nullptr);
		auto pyramid = (pyr_iter != _figures.end()) ? 
			*pyr_iter : MovableFigure(nullptr);

		auto key = _keyboard_listener.get_active_key();
		if (parallelepiped.exist() &&
			key > KeyboardListener::Key::FIGURE1 &&
			key < KeyboardListener::Key::FIGURE2) 
		{
			parallelepiped.change_state(MovableFigure::MoveState::MOVED);
		}
		if (pyramid.exist() && 
			key > KeyboardListener::Key::FIGURE2 &&
			key < KeyboardListener::Key::ESC) 
		{
			pyramid.change_state(MovableFigure::MoveState::MOVED);
		}

		if (parallelepiped.exist()) {
			switch (key) {
			case KeyboardListener::Key::ESC:
				return;
				break;
			case KeyboardListener::Key::A:
				parallelepiped.figure()->displace(Sides::LEFT, _parameters.move_step);
				break;
			case KeyboardListener::Key::S:
				parallelepiped.figure()->displace(Sides::DOWN, _parameters.move_step);
				break;
			case KeyboardListener::Key::D:
				parallelepiped.figure()->displace(Sides::RIGHT, _parameters.move_step);
				break;
			case KeyboardListener::Key::W:
				parallelepiped.figure()->displace(Sides::UP, _parameters.move_step);
				break;

			case KeyboardListener::Key::Q:
				parallelepiped.figure()->scale(1.0 - _parameters.scale_step);
				break;
			case KeyboardListener::Key::E:
				parallelepiped.figure()->scale(1.0 + _parameters.scale_step);
				break;

			case KeyboardListener::Key::Z:
				parallelepiped.figure()->spin(Axes::X, -_parameters.angle_step);
				break;
			case KeyboardListener::Key::X:
				parallelepiped.figure()->spin(Axes::X, _parameters.angle_step);
				break;
			case KeyboardListener::Key::C:
				parallelepiped.figure()->spin(Axes::Y, -_parameters.angle_step);
				break;
			case KeyboardListener::Key::V:
				parallelepiped.figure()->spin(Axes::Y, _parameters.angle_step);
				break;
			case KeyboardListener::Key::F:
				parallelepiped.figure()->spin(Axes::Z, -_parameters.angle_step);
				break;
			case KeyboardListener::Key::G:
				parallelepiped.figure()->spin(Axes::Z, _parameters.angle_step);
				break;

			case KeyboardListener::Key::R:
				parallelepiped.figure()->displace(Sides::CLOSER, _parameters.move_step);
				break;
			case KeyboardListener::Key::T:
				parallelepiped.figure()->displace(Sides::FURTHER, _parameters.move_step);
				break;
			case KeyboardListener::Key::NONE:
				break;
			default:
				break;
			}
		}

		if (pyramid.exist()) {
			switch (key) {
			case KeyboardListener::Key::J:
				pyramid.figure()->displace(Sides::LEFT, _parameters.move_step);
				break;
			case KeyboardListener::Key::K:
				pyramid.figure()->displace(Sides::DOWN, _parameters.move_step);
				break;
			case KeyboardListener::Key::L:
				pyramid.figure()->displace(Sides::RIGHT, _parameters.move_step);
				break;
			case KeyboardListener::Key::I:
				pyramid.figure()->displace(Sides::UP, _parameters.move_step);
				break;

			case KeyboardListener::Key::U:
				pyramid.figure()->scale(1.0 - _parameters.scale_step);
				break;
			case KeyboardListener::Key::O:
				pyramid.figure()->scale(1.0 + _parameters.scale_step);
				break;

			case KeyboardListener::Key::B:
				pyramid.figure()->spin(Axes::X, -_parameters.angle_step);
				break;
			case KeyboardListener::Key::N:
				pyramid.figure()->spin(Axes::X, _parameters.angle_step);
				break;
			case KeyboardListener::Key::M:
				pyramid.figure()->spin(Axes::Y, -_parameters.angle_step);
				break;
			case KeyboardListener::Key::P:
				pyramid.figure()->spin(Axes::Y, _parameters.angle_step);
				break;
			case KeyboardListener::Key::Y:
				pyramid.figure()->spin(Axes::Z, -_parameters.angle_step);
				break;
			case KeyboardListener::Key::H:
				pyramid.figure()->spin(Axes::Z, _parameters.angle_step);
				break;
			case KeyboardListener::Key::K9:
				pyramid.figure()->displace(Sides::CLOSER, _parameters.move_step);
				break;
			case KeyboardListener::Key::K0:
				pyramid.figure()->displace(Sides::FURTHER, _parameters.move_step);
				break;
			case KeyboardListener::Key::NONE:
				break;
			default:
				break;
			}
		}
	}

}
