#include "point.h"
#include "parallelepiped.h"
#include "triangularpyramid.h"
#include "scene.h"

int main(int argc, char* argv[])
{
	using tua::Point;
	using tua::Parallelepiped;
	using tua::TriangularPyramid;
	using tua::Scene;

	Point base0(100, 100, 100);
	Parallelepiped * par = new Parallelepiped(base0, 60, 30, 30, CYAN);
	Point base1(100, 100, 100);
	TriangularPyramid * pyr = new TriangularPyramid(base1, 60, MAGENTA);

	Scene scene("SCENE");
	scene.add_figure(par);
	scene.add_figure(pyr);
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