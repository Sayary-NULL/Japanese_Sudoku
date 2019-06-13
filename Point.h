#pragma once
#include "glut.h"

struct point
{
	double x, y;

	point(double X = 0, double Y = 0)
	{
		x = X;
		y = Y;
	}

	void Draw()
	{
		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
	}
};