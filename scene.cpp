#include "scene.h"

namespace tua {

	void instruct();

	void Scene::run() const
	{
		Point base(100, 100, 100);

		Parallelepiped par(base, 100, 300, 200);

		instruct();
		initwindow(960, 540, "SCENE");
		par.draw();

		while (true)
		{
			if (GetKeyState(TUA_ESC) & 0x8000)
				break;

			if (GetKeyState('A') & 0x8000)
			{
				par.displace(tua::Sides::LEFT, TUA_DIST);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('D') & 0x8000)
			{
				par.displace(tua::Sides::RIGHT, TUA_DIST);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('S') & 0x8000)
			{
				par.displace(tua::Sides::DOWN, TUA_DIST);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('W') & 0x8000)
			{
				par.displace(tua::Sides::UP, TUA_DIST);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('R') & 0x8000)
			{
				par.displace(tua::Sides::FURTHER, TUA_DIST);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('T') & 0x8000)
			{
				par.displace(tua::Sides::CLOSER, TUA_DIST);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('Z') & 0x8000)
			{
				par.spin(tua::Axes::X, -TUA_ALPHA);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('X') & 0x8000)
			{
				par.spin(tua::Axes::X, TUA_ALPHA);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('C') & 0x8000)
			{
				par.spin(tua::Axes::Y, -TUA_ALPHA);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('V') & 0x8000)
			{
				par.spin(tua::Axes::Y, TUA_ALPHA);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('B') & 0x8000)
			{
				par.spin(tua::Axes::Z, -TUA_ALPHA);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('N') & 0x8000)
			{
				par.spin(tua::Axes::Z, TUA_ALPHA);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('Q') & 0x8000)
			{
				par.scale(TUA_DEC);
				clearviewport();
				par.draw();
			}

			if (GetKeyState('E') & 0x8000)
			{
				par.scale(TUA_INC);
				clearviewport();
				par.draw();
			}
		}

		getch();
		closegraph();
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

}