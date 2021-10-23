#include "keyboardlistener.h"
#include "scene.h"

tua::KeyboardListener::ProcessStatus tua::KeyboardListener::process_actions(Figure * figure, const MovementParameters & params) {

	if (!figure) {
		throw std::invalid_argument("KeyboardListener::process_actions(): figure was nullptr");
	}

	ProcessStatus process_status = ProcessStatus::ACTION_MISSED;
	if (figure->type() == Figure::FigureType::PARALLELEPIPED) {
		if (GetKeyState(ESCAPE) & 0x8000) {
			return ProcessStatus::QUIT;
		}

		if (GetKeyState('A') & 0x8000) {
			figure->displace(Sides::LEFT, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('D') & 0x8000) {
			figure->displace(Sides::RIGHT, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('S') & 0x8000) {
			figure->displace(Sides::DOWN, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('W') & 0x8000) {
			figure->displace(Sides::UP, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}

		if (GetKeyState('R') & 0x8000) {
			figure->displace(Sides::CLOSER, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('T') & 0x8000) {
			figure->displace(Sides::FURTHER, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}		
		
		if (GetKeyState('Z') & 0x8000) {
			figure->spin(Axes::X, -params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('X') & 0x8000) {
			figure->spin(Axes::X, params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('C') & 0x8000) {
			figure->spin(Axes::Y, -params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('V') & 0x8000) {
			figure->spin(Axes::Y, params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('F') & 0x8000) {
			figure->spin(Axes::Z, -params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('G') & 0x8000) {
			figure->spin(Axes::Z, params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}

		if (GetKeyState('Q') & 0x8000) {
			figure->scale(1.0 - params.scale_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('E') & 0x8000) {
			figure->scale(1.0 + params.scale_step);
			process_status = ProcessStatus::ACTION_DONE;
		}		
	}
	else if (figure->type() == Figure::FigureType::TRIANGULAR_PYRAMID) {
		if (GetKeyState(ESCAPE) & 0x8000) {
			return ProcessStatus::QUIT;
		}

		if (GetKeyState('J') & 0x8000) {
			figure->displace(Sides::LEFT, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('L') & 0x8000) {
			figure->displace(Sides::RIGHT, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('K') & 0x8000) {
			figure->displace(Sides::DOWN, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('I') & 0x8000) {
			figure->displace(Sides::UP, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}

		if (GetKeyState('9') & 0x8000) {
			figure->displace(Sides::CLOSER, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('0') & 0x8000) {
			figure->displace(Sides::FURTHER, params.move_step);
			process_status = ProcessStatus::ACTION_DONE;
		}

		if (GetKeyState('B') & 0x8000) {
			figure->spin(Axes::X, -params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('N') & 0x8000) {
			figure->spin(Axes::X, params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('M') & 0x8000) {
			figure->spin(Axes::Y, -params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('P') & 0x8000) {
			figure->spin(Axes::Y, params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('Y') & 0x8000) {
			figure->spin(Axes::Z, -params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('H') & 0x8000) {
			figure->spin(Axes::Z, params.angle_step);
			process_status = ProcessStatus::ACTION_DONE;
		}

		if (GetKeyState('O') & 0x8000) {
			figure->scale(1.0 - params.scale_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
		if (GetKeyState('U') & 0x8000) {
			figure->scale(1.0 + params.scale_step);
			process_status = ProcessStatus::ACTION_DONE;
		}
	}

	return process_status;
}