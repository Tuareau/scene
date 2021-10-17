#include "keyboardlistener.h"

tua::KeyboardListener::Key tua::KeyboardListener::get_active_key() const {
	if (GetKeyState(ESCAPE) & 0x8000) {
		return Key::ESC;
	}
	if (GetKeyState('A') & 0x8000) {
		return Key::A;
	}
	if (GetKeyState('D') & 0x8000) {
		return Key::D;
	}
	if (GetKeyState('S') & 0x8000) {
		return Key::S;
	}
	if (GetKeyState('W') & 0x8000) {
		return Key::W;
	}
	if (GetKeyState('R') & 0x8000) {
		return Key::R;
	}
	if (GetKeyState('T') & 0x8000) {
		return Key::T;
	}
	if (GetKeyState('Z') & 0x8000) {
		return Key::Z;
	}
	if (GetKeyState('X') & 0x8000) {
		return Key::X;
	}
	if (GetKeyState('C') & 0x8000) {
		return Key::C;
	}
	if (GetKeyState('V') & 0x8000) {
		return Key::V;
	}
	if (GetKeyState('F') & 0x8000) {
		return Key::F;
	}
	if (GetKeyState('G') & 0x8000) {
		return Key::G;
	}
	if (GetKeyState('Q') & 0x8000) {
		return Key::Q;
	}
	if (GetKeyState('E') & 0x8000) {
		return Key::E;
	}
	if (GetKeyState('J') & 0x8000) {
		return Key::J;
	}
	if (GetKeyState('L') & 0x8000) {
		return Key::L;
	}
	if (GetKeyState('K') & 0x8000) {
		return Key::K;
	}
	if (GetKeyState('I') & 0x8000) {
		return Key::I;
	}
	if (GetKeyState('9') & 0x8000) {
		return Key::K9;
	}
	if (GetKeyState('0') & 0x8000) {
		return Key::K0;
	}
	if (GetKeyState('B') & 0x8000) {
		return Key::B;
	}
	if (GetKeyState('N') & 0x8000) {
		return Key::N;
	}
	if (GetKeyState('M') & 0x8000) {
		return Key::M;
	}
	if (GetKeyState('P') & 0x8000) {
		return Key::P;
	}
	if (GetKeyState('Y') & 0x8000) {
		return Key::Y;
	}
	if (GetKeyState('H') & 0x8000) {
		return Key::H;
	}
	if (GetKeyState('O') & 0x8000) {
		return Key::O;
	}
	if (GetKeyState('U') & 0x8000) {
		return Key::U;
	}
	return Key::NONE;
}