#include <vcl.h>
#include "ZBuffer3.h"
#include <math.h>
#include <stdio.h>
#include <malloc.h>

#define MAX_DEPTH 1000.0 //������������ ������� �����
#define MAX_Y_LINES 200 //������������ ���������� ����� � �����.
#define BG_COLOR 3; //���� �� ���������

//��������� ��� ����� � 3-������ ������������.
struct Point {
	double x, y, z;
};

//��������� ������, �� ������� ����� �������� Z-�����.
struct Cell {
	double z;
	int color;
};

//����� �������������.
class Triangle {
public:
	int color;
	Point points[3];
	Triangle(Point p1, Point p2, Point p3, int c) {
		points[0] = p1; points[1] = p2; points[2] = p3;
		color = c;
	}
};

//����� Z-������.
class ZBuffer {
public:
	Cell *buff[MAX_Y_LINES];
	int sizeX, sizeY;	// ������ Z-������
	ZBuffer(int, int);
	~ZBuffer();
	void PutTriangle(Triangle&);
	void Show();
	void Clear();
};

//����������� Z-������.
ZBuffer::ZBuffer(int ax, int ay) {
	sizeX = ax; sizeY = ay;
	for (int i = 0; i < sizeY; i++) {
		buff[i] = (struct Cell *)malloc(sizeX * sizeof(struct Cell));
	}
}

//���������� Z-������.
ZBuffer::~ZBuffer() {
	for (int i = 0; i < sizeY; i++)
		free(buff[i]);
}

//�������, ��������� �� ����� ���������� ������������ Z-������.
void ZBuffer::Show() {
	for (int j = 0; j < sizeY; j++)
		for (int i = 0; i < sizeX; i++);
			//������� ������� �� �����
			// putpixel();
}

//�������, '���������' Z-�����.
void ZBuffer::Clear() {
	for (int j = 0; j < sizeY; j++)
		for (int i = 0; i < sizeX; i++)
			(*(buff[j] + i)).z = MAX_DEPTH, (*(buff[j] + i)).color = BG_COLOR;
}

void ZBuffer::PutTriangle(Triangle& t) {
	int triangle_y_max, triangle_y_min;
	int x[3], y[3];
	//������� x,y �� t � ������� ��� ����������� ������ � ����
	for (int i = 0; i < 3; i++)
		x[i] = int(t.points[i].x), y[i] = int(t.points[i].y);


	//���������� ������������ � ����������� y
	triangle_y_max = triangle_y_min = y[0];
	if (triangle_y_max < y[1]) triangle_y_max = y[1]; else if (triangle_y_min > y[1]) triangle_y_min = y[1];
	if (triangle_y_max < y[2]) triangle_y_max = y[2]; else if (triangle_y_min > y[2]) triangle_y_min = y[2];
	triangle_y_min = (triangle_y_min < 0) ? 0 : triangle_y_min;
	triangle_y_max = (triangle_y_max < sizeY) ? triangle_y_max : sizeY;

	int y_index, e1;
	int ne;
	int x1, x2, xsc1, xsc2;
	double z1, z2, tc;
	//��������� ������� ���� ���������� ��� ������ �����
	//� ���������� ������� ������� �������
	//��� ���������������� ������������
	for (y_index = triangle_y_min; y_index < triangle_y_max; y_index++) {
		ne = 0;
		for (int e = 0; e < 3; e++) {
			e1 = e + 1;
			if (e1 == 3) e1 = 0;

			if (y[e] < y[e1]) {
				if (y[e1] <= y_index || y_index < y[e]) continue;
			}
			else if (y[e] > y[e1]) {
				if (y[e1] > y_index || y_index >= y[e]) continue;
			}
			else continue;

			tc = double(y[e] - y_index) / (y[e] - y[e1]);

			if (ne)
				x2 = x[e] + int(tc * (x[e1] - x[e])),
				z2 = t.points[e].z + tc * (t.points[e1].z - t.points[e].z);
			else
				x1 = x[e] + int(tc * (x[e1] - x[e])),
				z1 = t.points[e].z + tc * (t.points[e1].z - t.points[e].z),
				ne = 1;
		}


		int e;
		if (x2 < x1) e = x1, x1 = x2, x2 = e, tc = z1, z1 = z2, z2 = tc;
		xsc1 = (x1 < 0) ? 0 : x1;
		xsc2 = (x2 < sizeX) ? x2 : sizeX;

		double z;
		for (int xsc = xsc1; xsc < xsc2; xsc++) {
			tc = double(x1 - xsc) / (x1 - x2);
			z = z1 + tc * (z2 - z1);
			//���� ���������� ������� ������� ������ ���,
			//��� ��������� � Z-������ - �������� ���������� �� �����.
			if (z < (*(buff[y_index] + xsc)).z)
				(*(buff[y_index] + xsc)).color = t.color,
				(*(buff[y_index] + xsc)).z = z;
		}
	}
}

//������� 6 ������� ����� ��� 6 �������������, x,y,z ��������������.
Point points[6][3] = {
{{  20.0,  60.0,  50.0}, {  60.0,  20.0,  50.0}, { 180.0, 140.0,   0.0}},
{{  80.0,  20.0,   0.0}, {  80.0, 180.0,  50.0}, {  40.0, 160.0,  50.0}},
{{  20.0, 140.0,   0.0}, { 150.0,  60.0,  50.0}, { 180.0, 100.0,  50.0}},
{{  90.0,  10.0, 100.0}, {  10.0,  90.0, 100.0}, { 210.0, 190.0, 100.0}},
{{ 100.0,  50.0, 100.0}, { 100.0, 150.0,   0.0}, { 200.0, 100.0,  50.0}},
{{  50.0, 100.0,  50.0}, { 150.0, 150.0, 100.0}, { 150.0,  50.0,   0.0}},
};

//�������������� ������������.
Triangle	t1(points[0][0], points[0][1], points[0][2], 13),
t2(points[1][0], points[1][1], points[1][2], 14),
t3(points[2][0], points[2][1], points[2][2], 12),
t4(points[3][0], points[3][1], points[3][2], 10),
t5(points[4][0], points[4][1], points[4][2], 11),
t6(points[5][0], points[5][1], points[5][2], 9);

//�������, ��������������� ������ ��������� Z-������.
void Buffer() {
	ZBuffer * zb;
	zb = new ZBuffer(220, 200); //������� Z-����� � ������� ���������
	zb->Clear(); //�������������� � ����������
	//��������� Z-�����
	zb->PutTriangle(t1);
	zb->PutTriangle(t2);
	zb->PutTriangle(t3);
	zb->PutTriangle(t4);
	zb->PutTriangle(t5);
	zb->PutTriangle(t6);
	//������� ���������� �� �����
	zb->Show();
}