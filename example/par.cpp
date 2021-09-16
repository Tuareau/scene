#include "par.h"

Par::Par()
{
    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
        {
            if (j == Y - 1)
                R[i][j] = 1.0;
            else
                R[i][j] = 0.0;
        }
}

void Par::setdefault()
{
    R[0][0] = 100; R[0][1] = 150; R[0][2] = 100;
    R[1][0] = 400; R[1][1] = 150; R[1][2] = 100;

    R[2][0] = 400; R[2][1] = 350; R[2][2] = 100;
    R[3][0] = 100; R[3][1] = 350; R[3][2] = 100;

    R[4][0] = 100; R[4][1] = 150; R[4][2] = 300;
    R[5][0] = 400; R[5][1] = 150; R[5][2] = 300;

    R[6][0] = 400; R[6][1] = 350; R[6][2] = 300;
    R[7][0] = 100; R[7][1] = 350; R[7][2] = 300;
}

void Par::multiply(double N[Y][Y])
{
    double S[X][Y];
    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
            S[i][j] = 0.0;

	for (int k = 0; k < X; k++)
		for (int i = 0; i < Y; i++)
			for (int j = 0; j < Y; j++)
				S[k][i] += R[k][j] * N[j][i];

    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
            R[i][j] = S[i][j];
}

void Par::multiply(double B[X][Y], double N[Y][Y])
{
    double S[X][Y];
    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
            S[i][j] = 0.0;

	for (int k = 0; k < X; k++)
		for (int i = 0; i < Y; i++)
			for (int j = 0; j < Y; j++)
				S[k][i] += B[k][j] * N[j][i];

    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
            B[i][j] = S[i][j];
}

void Par::draw(int color)
{
    double a = 3.14 / 180 * 30;

    double Rcopy[X][Y];
    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
            Rcopy[i][j] = R[i][j];

    double P0[Y][Y] = {
        {cos(a),  0, sin(a),0},
        {0, 1, 0, 0},
        {-sin(a), 0, cos(a), 0},
        {0, 0, 0, 1},
    };

    multiply(Rcopy, P0);

    setcolor(color);
	line(Rcopy[0][0], Rcopy[0][1], Rcopy[3][0], Rcopy[3][1]);
	for (int i = 0; i < 3; i++)
        line(Rcopy[i][0], Rcopy[i][1], Rcopy[i+1][0], Rcopy[i+1][1]);

    line(Rcopy[4][0], Rcopy[4][1], Rcopy[7][0], Rcopy[7][1]);
	for (int i = 4; i < X - 1; i++)
        line(Rcopy[i][0], Rcopy[i][1], Rcopy[i+1][0], Rcopy[i+1][1]);

    for (int i = 0; i < 4; i++)
        line(Rcopy[i][0], Rcopy[i][1], Rcopy[i+4][0], Rcopy[i+4][1]);
}

void Par::displace(double dx, double dy, double dz)
{
	// ������� �����������
	double N[Y][Y] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{dx,dy,dz,1}
	};
	multiply(N);
}

void Par::spin(double angle, axes A)
{
	using std::cos;
	using std::sin;

	double rad = 3.14 / 180 * angle;
	double c = cos(rad), s = sin(rad);

	double x = 0;
	double y = 0;
	double z = 0;
    for (int i = 0; i < X; i++)
    {
        x += R[i][0];
        y += R[i][1];
        z += R[i][2];
    }
    x /= X;
    y /= X;
    z /= X;

	// ������� �������� ������ ����
	double Xspin[Y][Y] = {
	    {1,0,0,0},
		{0,c,s,0},
		{0,-s,c,0},
		{0,y*(1 - c) + z * s, z*(1 - c) - y * s, 1}
	};
    double Yspin[Y][Y] = {
		{c,0,-s,0},
		{0,1,0,0},
		{s,0,c,0},
		{x*(1 - c) - z * s, 0, z*(1 - c) + x * s, 1}
	};
    double Zspin[Y][Y] = {
        {c,s,0,0},
        {-s,c,0,0},
		{0,0,1,0},
		{x*(1 - c) + y * s, y*(1 - c) - x * s, 0, 1}
	};

	switch (A)
	{
        case axes::X:
            multiply(Xspin);
            break;
        case axes::Y:
            multiply(Yspin);
            break;
        case axes::Z:
            multiply(Zspin);
            break;
	}
}

void Par::scale(double step)
{
	double x = 0;
	double y = 0;
    double z = 0;
    for (int i = 0; i < X; i++)
    {
        x += R[i][0];
        y += R[i][1];
        z += R[i][2];
    }
    x /= X;
    y /= X;
    z /= X;

	// ������� ��������������� ������������ �����
	double N[Y][Y] = {
		{step,0,0,0},
		{0,step,0,0},
		{0,0,step,0},
		{x*(1 - step), y*(1 - step), z*(1 - step), 1},
	};
	multiply(N);
}