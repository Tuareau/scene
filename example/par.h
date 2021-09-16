#ifndef PAR_H_INCLUDED
#define PAR_H_INCLUDED

#include <iostream>
#include <cmath>
#include "graphics.h"

class Par
{
private:
	enum matrix { X = 8, Y = 4 };
	double R[X][Y];
    void multiply(double N[Y][Y]);
    void multiply(double B[X][Y], double N[Y][Y]);
public:
	Par();
	~Par() {}

	void setdefault();
	void draw(int color = WHITE);

    enum class axes {X, Y, Z};
	void displace(double dx, double dy, double dz);
	void spin(double degree, axes A);
	void scale(double step);
};

#endif // PAR_H_INCLUDED
