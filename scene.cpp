#include "scene.h"

namespace tua {

	Scene::Scene(const std::string & title, size_t width, size_t height)
		: _figure0(nullptr), _figure1(nullptr) {
		initwindow(width, height, title.c_str());
	}

	void Scene::add_figure(Figure * figure) {
		if (!_figure0) _figure0 = figure;
		if (!_figure1) _figure1 = figure;
	}

	void Scene::set_objects_movement(double distance, double alpha, double increase, double decrease) {
		_parameters = { distance, alpha, increase, decrease };
	}

	Scene::~Scene() {
		//delete _buffer;
		closegraph(ALL_WINDOWS);
	}

	void Scene::show_instruction() const {
		using std::cout;
		cout << "\nThe instruction of using\n";
		cout << "\nPAR\n";
		cout << "Move: A, S, D, W, R, T\n";
		cout << "Rotate: (Z, X), (C, V), (B, N)\n";
		cout << "Scale: Q, E\n";
		cout << "Press ESC to quit\n";
	}

	void Scene::draw_figures() const {
		if (_figure0) _figure0->draw();
		if (_figure1) _figure1->draw();
	}

	void Scene::run() const {
		show_instruction();
		draw_figures();

		while (true)
		{
			if (GetKeyState(ESC) & 0x8000)
				break;

			if (GetKeyState('A') & 0x8000) {
				_figure0->displace(tua::Sides::LEFT, _parameters.distance);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('D') & 0x8000) {
				_figure0->displace(tua::Sides::RIGHT, _parameters.distance);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('S') & 0x8000) {
				_figure0->displace(tua::Sides::DOWN, _parameters.distance);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('W') & 0x8000) {
				_figure0->displace(tua::Sides::UP, _parameters.distance);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('R') & 0x8000) {
				_figure0->displace(tua::Sides::CLOSER, _parameters.distance);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('T') & 0x8000) {
				_figure0->displace(tua::Sides::FURTHER, _parameters.distance);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('Z') & 0x8000) {
				_figure0->spin(tua::Axes::X, -_parameters.alpha);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('X') & 0x8000) {
				_figure0->spin(tua::Axes::X, _parameters.alpha);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('C') & 0x8000) {
				_figure0->spin(tua::Axes::Y, -_parameters.alpha);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('V') & 0x8000) {
				_figure0->spin(tua::Axes::Y, _parameters.alpha);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('B') & 0x8000) {
				_figure0->spin(tua::Axes::Z, -_parameters.alpha);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('N') & 0x8000) {
				_figure0->spin(tua::Axes::Z, _parameters.alpha);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('Q') & 0x8000) {
				_figure0->scale(_parameters.scale_dec);
				clearviewport();
				draw_figures();
			}
			if (GetKeyState('E') & 0x8000) {
				_figure0->scale(_parameters.scale_inc);
				clearviewport();
				draw_figures();
			}
		}
		getch();
	}
}