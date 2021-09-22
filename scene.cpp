#include "scene.h"

namespace tua {

	Scene::Scene(const std::string & title, size_t width, size_t height) {
		initwindow(width, height, title.c_str());
		//_buffer = new DepthBuffer(width, height, BLACK);
	}

	void Scene::add_figure(Figure * figure) {
		if (_figures.size() < _objects_max_count)
			_figures.push_back(figure);
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
		cout << std::setw(40) << "\nThe instruction of using\n";
		for (const auto & figure : _figures) {
			if (dynamic_cast<Parallelepiped *>(figure)) {
				cout << std::setw(40) << "\nPARALLELEPIPED\n";
				cout << std::setw(40) << "Move: A, S, D, W, R, T\n";
				cout << std::setw(40) << "Rotate: (Z, X), (C, V), (F, G)\n";
				cout << std::setw(40) << "Scale: Q, E\n";
			}
			else if (dynamic_cast<TriangularPyramid *>(figure)) {
				cout << std::setw(40) << "\nTRIANGULAR PYRAMID\n";
				cout << std::setw(40) << "Move: I, J, K, L, 9, 0\n";
				cout << std::setw(40) << "Rotate: (B, N), (M, P), (Y, H)\n";
				cout << std::setw(40) << "Scale: U, O\n";
			}
		}
		cout << std::setw(40) << "Press ESC to quit\n" << std::endl;
	}

	void Scene::draw_figures() const {
		for (const auto & figure : _figures)
			figure->draw();
		//if (_figure0) _figure0->draw(_buffer);
		//if (_figure1) _figure1->draw(_buffer);
	}

	//void Scene::update_buffer() {
	//	if (_figure0) _figure0->fill_depth_buffer(_buffer);
	//	if (_figure1) _figure1->fill_depth_buffer(_buffer);
	//}

	void Scene::run() {
		show_instruction();
		draw_figures();

		while (true)
		{
			if (GetKeyState(ESC) & 0x8000)
				break;

			if (GetKeyState('A') & 0x8000) {
				_figures[0]->displace(tua::Sides::LEFT, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('D') & 0x8000) {
				_figures[0]->displace(tua::Sides::RIGHT, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('S') & 0x8000) {
				_figures[0]->displace(tua::Sides::DOWN, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('W') & 0x8000) {
				_figures[0]->displace(tua::Sides::UP, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('R') & 0x8000) {
				_figures[0]->displace(tua::Sides::CLOSER, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('T') & 0x8000) {
				_figures[0]->displace(tua::Sides::FURTHER, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('Z') & 0x8000) {
				_figures[0]->spin(tua::Axes::X, -_parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('X') & 0x8000) {
				_figures[0]->spin(tua::Axes::X, _parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('C') & 0x8000) {
				_figures[0]->spin(tua::Axes::Y, -_parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('V') & 0x8000) {
				_figures[0]->spin(tua::Axes::Y, _parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('F') & 0x8000) {
				_figures[0]->spin(tua::Axes::Z, -_parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('G') & 0x8000) {
				_figures[0]->spin(tua::Axes::Z, _parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('Q') & 0x8000) {
				_figures[0]->scale(_parameters.scale_dec);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('E') & 0x8000) {
				_figures[0]->scale(_parameters.scale_inc);
				clearviewport();
				//update_buffer();
				draw_figures();
			}


			if (GetKeyState('J') & 0x8000) {
				_figures[1]->displace(tua::Sides::LEFT, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('L') & 0x8000) {
				_figures[1]->displace(tua::Sides::RIGHT, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('K') & 0x8000) {
				_figures[1]->displace(tua::Sides::DOWN, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('I') & 0x8000) {
				_figures[1]->displace(tua::Sides::UP, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('9') & 0x8000) {
				_figures[1]->displace(tua::Sides::CLOSER, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('0') & 0x8000) {
				_figures[1]->displace(tua::Sides::FURTHER, _parameters.distance);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('B') & 0x8000) {
				_figures[1]->spin(tua::Axes::X, -_parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('N') & 0x8000) {
				_figures[1]->spin(tua::Axes::X, _parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('M') & 0x8000) {
				_figures[1]->spin(tua::Axes::Y, -_parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('P') & 0x8000) {
				_figures[1]->spin(tua::Axes::Y, _parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('Y') & 0x8000) {
				_figures[1]->spin(tua::Axes::Z, -_parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('H') & 0x8000) {
				_figures[1]->spin(tua::Axes::Z, _parameters.alpha);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('U') & 0x8000) {
				_figures[1]->scale(_parameters.scale_dec);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
			if (GetKeyState('O') & 0x8000) {
				_figures[1]->scale(_parameters.scale_inc);
				clearviewport();
				//update_buffer();
				draw_figures();
			}
		}
		getch();
	}
}