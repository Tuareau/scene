#include "point.h"
#include "parallelepiped.h"
#include "triangularpyramid.h"
#include "scene.h"
#include "color.h"
#include "axes.h"
#include "ground.h"

int main(int argc, char* argv[])
{
	using tua::Point;
	using tua::Parallelepiped;
	using tua::TriangularPyramid;
	using tua::Scene;
	using tua::Axes;

	Point base0(100, 100, 0);
	Parallelepiped * par = new Parallelepiped(base0, 60, 30, 30, Color::CYAN);
	Point base1(100, 100, 0);
	TriangularPyramid * pyr = new TriangularPyramid(base1, 60, Color::MAGENTA);

	Scene scene("SCENE");
	scene.add_figure(par);
	scene.add_figure(pyr);
	scene.turn_light_on();
	scene.rotate_axes(Axes::X, 45);
	scene.rotate_axes(Axes::Y, 45);
	scene.run();

	delete par;
	delete pyr;
}

//#include <cstdlib>
//#include <string>
//#include <iostream>
//
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//	string command = "g++ ";
//	string blank = " ";
//	int i;
//
//	for (i = 1; i < argc; i++)
//		command += blank + argv[i];
//
//#ifdef WINDOWS
//	command += " -mwindows";
//#endif
//	command += " -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32";
//
//	return system(command.c_str());
//}