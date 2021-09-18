#include <iostream>
#include <cctype>

#include "graphics.h"

#include "parallelepiped.h"
#include "point.h"

#define ESC 27
#define DIST 0.5 // смещение
#define ALPHA 0.2 // угол
#define INC 1.01 // коэф. для увеличения
#define DEC 0.99 // коэф. для уменьшения

void instruct();

int main_scene()
{
	tua::Point base(100, 100, 100);

	tua::Parallelepiped par(base, 100, 300, 200);
	
	instruct();
	initwindow(960, 540, "SCENE");
	par.draw();

	while (true)
	{
		if (GetKeyState(ESC) & 0x8000)
			break;

		if (GetKeyState('A') & 0x8000)
		{
			par.displace(tua::Sides::LEFT, DIST);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('D') & 0x8000)
		{
			par.displace(tua::Sides::RIGHT, DIST);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('S') & 0x8000)
		{
			par.displace(tua::Sides::DOWN, DIST);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('W') & 0x8000)
		{
			par.displace(tua::Sides::UP, DIST);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('R') & 0x8000)
		{
			par.displace(tua::Sides::FURTHER, DIST);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('T') & 0x8000)
		{
			par.displace(tua::Sides::CLOSER, DIST);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('Z') & 0x8000)
		{
			par.spin(tua::Axes::X, -ALPHA);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('X') & 0x8000)
		{
			par.spin(tua::Axes::X, ALPHA);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('C') & 0x8000)
		{
			par.spin(tua::Axes::Y, -ALPHA);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('V') & 0x8000)
		{
			par.spin(tua::Axes::Y, ALPHA);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('B') & 0x8000)
		{
			par.spin(tua::Axes::Z, -ALPHA);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('N') & 0x8000)
		{
			par.spin(tua::Axes::Z, ALPHA);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('Q') & 0x8000)
		{
			par.scale(DEC);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('E') & 0x8000)
		{
			par.scale(INC);
			clearviewport();
			par.draw();
		}
	}

	getch();
	closegraph();
	return 0;
}

void instruct()
{
	using std::cout;

	cout << "\nThe instruction of using\n";

	cout << "\nPAR\n";
	cout << "Move: A, S, D, W, R, T\n";
	cout << "Rotate: (Z, X), (C, V), (B, N)\n";
	cout << "Scale: Q, E\n";

	cout << "Press ESC to quit\n";
}