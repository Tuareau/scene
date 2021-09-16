/* 
#include <iostream>
#include <cctype>
#include "par.h"

#define ESC 27
#define DIST 0.5 // смещение
#define ALPHA 0.2 // угол
#define INC 1.01 // коэф. для увеличения
#define DEC 0.99 // коэф. для уменьшения

void instruct();

int main()
{
	Par par;
	par.setdefault();

	instruct();
	initwindow(960, 540, "PAR");
	par.draw();

	while (true)
	{
		if (GetKeyState(ESC) & 0x8000)
			break;

		if (GetKeyState('A') & 0x8000)
		{
			par.displace(-DIST, 0, 0);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('D') & 0x8000)
		{
			par.displace(DIST, 0, 0);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('S') & 0x8000)
		{
			par.displace(0, DIST, 0);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('W') & 0x8000)
		{
			par.displace(0, -DIST, 0);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('R') & 0x8000)
		{
			par.displace(0, 0, DIST);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('T') & 0x8000)
		{
			par.displace(0, 0, -DIST);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('Z') & 0x8000)
		{
			par.spin(-ALPHA, Par::axes::X);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('X') & 0x8000)
		{
			par.spin(ALPHA, Par::axes::X);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('C') & 0x8000)
		{
			par.spin(-ALPHA, Par::axes::Y);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('V') & 0x8000)
		{
			par.spin(ALPHA, Par::axes::Y);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('B') & 0x8000)
		{
			par.spin(-ALPHA, Par::axes::Z);
			clearviewport();
			par.draw();
		}

		if (GetKeyState('N') & 0x8000)
		{
			par.spin(ALPHA, Par::axes::Z);
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
*/