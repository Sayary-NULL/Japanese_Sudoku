#include "DrawNumber.h"
#include "glut.h"

void Draw0(point p1, point p2);
void Draw1(point p1, point p2);
void Draw2(point p1, point p2);
void Draw3(point p1, point p2);
void Draw4(point p1, point p2);
void Draw5(point p1, point p2);
void Draw6(point p1, point p2);
void Draw7(point p1, point p2);
void Draw8(point p1, point p2);
void Draw9(point p1, point p2);

void DrawNumber(const char number, point p1, double len, double c)
{
	if (number == '0')
		Draw0(p1, point(p1.x + len, p1.y - len*c));
	else if(number == '1')
		Draw1(p1, point(p1.x + len, p1.y - len * c));
	else if(number == '2')
		Draw2(p1, point(p1.x + len, p1.y - len * c));
	else if(number == '3')
		Draw3(p1, point(p1.x + len, p1.y - len * c));
	else if (number == '4')
		Draw4(p1, point(p1.x + len, p1.y - len * c));
	else if(number == '5')
		Draw5(p1, point(p1.x + len, p1.y - len * c));
	else if (number == '6')
		Draw6(p1, point(p1.x + len, p1.y - len * c));
	else if (number == '7')
		Draw7(p1, point(p1.x + len, p1.y - len * c));
	else if (number == '8')
		Draw8(p1, point(p1.x + len, p1.y - len * c));
	else if (number == '9')
		Draw9(p1, point(p1.x + len, p1.y - len * c));
}

void Draw0(point p1, point p2)
{
	glBegin(GL_LINE_STRIP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p1.x, p1.y);
	glEnd();
}

void Draw1(point p1, point p2)
{
	glBegin(GL_LINE_STRIP);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glEnd();
}

void Draw2(point p1, point p2)
{
	double dy = (p2.y - p1.y) / 2;
	glBegin(GL_LINE_STRIP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p2.x, p1.y + dy);
	glVertex2d(p1.x, p1.y + dy);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glEnd();
}

void Draw3(point p1, point p2)
{
	double dy = (p2.y - p1.y) / 2;
	glBegin(GL_LINE_STRIP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p2.x, p1.y + dy);
	glVertex2d(p1.x, p1.y + dy);
	glVertex2d(p2.x, p1.y + dy);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p1.x, p2.y);
	glEnd();
}

void Draw4(point p1, point p2)
{
	double dy = (p2.y - p1.y) / 2;
	glBegin(GL_LINE_STRIP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p1.y + dy);
	glVertex2d(p2.x, p1.y + dy);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y);
	glEnd();
}

void Draw5(point p1, point p2)
{
	double dy = (p2.y - p1.y) / 2;
	glBegin(GL_LINE_STRIP);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p1.y + dy);
	glVertex2d(p2.x, p1.y + dy);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p1.x, p2.y);
	glEnd();
}

void Draw6(point p1, point p2)
{
	double dy = (p2.y - p1.y) / 2;
	glBegin(GL_LINE_STRIP);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y + dy);
	glVertex2d(p1.x, p1.y + dy);
	glEnd();
}

void Draw7(point p1, point p2)
{
	glBegin(GL_LINE_STRIP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glEnd();
}

void Draw8(point p1, point p2)
{
	double dy = (p2.y - p1.y) / 2;
	glBegin(GL_LINE_STRIP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p1.x, p1.y);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(p1.x, p1.y + dy);
	glVertex2d(p2.x, p1.y + dy);
	glEnd();
}

void Draw9(point p1, point p2)
{
	double dy = (p2.y - p1.y) / 2;
	glBegin(GL_LINE_STRIP);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p1.y + dy);
	glVertex2d(p2.x, p1.y + dy);
	glEnd();
}