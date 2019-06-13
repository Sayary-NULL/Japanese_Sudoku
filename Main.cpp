#include <iostream>
#include <vector>
#include <Windows.h>
#include <stdio.h>
#include "Field.h"
#include "DrawNumber.h"
#include "glut.h"

using namespace std;

double mousex = 0, mousey = 0;
GLfloat windowWidth = 640;
GLfloat windowHeight = 640;
Field field;
HWND hConsole = GetConsoleWindow();
int number = 1;
int MaxValue = 0;

void DrawLine(const point& t1, const point& t2) 
{
	glBegin(GL_LINES);
	glVertex2d(t1.x, t1.y);
	glVertex2d(t2.x, t2.y);
	glEnd();
}

void Text(const char* text, int x, int y) 
{
	glRasterPos2i(x, y); //позици€ текста
	for (int i = 0; i < strlen(text); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	
}

void Display()
{
	glClearColor(255, 255, 255, 1.0); //установка цвета окна (фон)
	glClear(GL_COLOR_BUFFER_BIT); //очистка окна текущим цветом
	glLineWidth(2); //толщина линии
	glColor3d(0, 0, 0);
	double x1 = -160, y1 = 160;
	double x2 = -160, y2 = -240;

	field.DrawField();

	point p1, p2;
	p1.x = windowWidth / 2 - 50; p1.y = 10;
	p2.x = windowWidth / 2 + 50; p2.y = 40;

	if (field.IsCheck) glColor3d(0, 1, 0);
	else glColor3d(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y);
	glEnd();

	glColor3d(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y);
	glEnd();

	glColor3d(0, 0, 0);
	Text("CHECK", windowWidth / 2 - 3*8, 20);

	p1.x = 10; p1.y = 40;
	p2.x = 40; p2.y = 10;

	glColor3d(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y);
	glEnd();

	glColor3d(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y);
	glEnd(); 

	double dx = (p2.x - p1.x) / 4;
	double dy = (p1.y - p2.y) / 4;
	point tr1(p1.x + dx, p2.y + (p1.y - p2.y) / 2), tr2(p1.x + 3 * dx, p1.y - dy), tr3(p1.x + 3*dx, p2.y + dy);

	glColor3d(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(tr1.x, tr1.y);
	glVertex2d(tr2.x, tr2.y);
	glVertex2d(tr3.x, tr3.y);
	glVertex2d(tr1.x, tr1.y);
	glEnd();

	p1.x = windowWidth - 40; p1.y = 40;
	p2.x = windowWidth - 10; p2.y = 10;

	glColor3d(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y);
	glEnd();

	glColor3d(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y);
	glEnd();

	dx = (p2.x - p1.x) / 4;
	dy = (p1.y - p2.y) / 4;
	point tr21(p1.x + 3*dx, p2.y + (p1.y - p2.y) / 2), tr22(p1.x + dx, p1.y - dy), tr23(p1.x + dx, p2.y + dy);

	glColor3d(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(tr21.x, tr21.y);
	glVertex2d(tr22.x, tr22.y);
	glVertex2d(tr23.x, tr23.y);
	glVertex2d(tr21.x, tr21.y);
	glEnd();

	glutSwapBuffers();
}

void Check() 
{
	/*bool o = true;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (A[i][j] != B[i][j]) {
				o = false;
				break;
			}
	isCheck = o;
	Prov = true;*/
}

void ChangeSize(int width, int height) 
{
	glutReshapeWindow(windowWidth, windowHeight);

	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, windowWidth, 0, windowHeight, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void LoadField()
{
	string file = "Field_";
	file += to_string(number);
	file += ".ini";

	field.DeleteInfo();
	field.LoadFile(file);

	windowHeight = field.WindowHeight;
	windowWidth = field.WindowWidth;
	ChangeSize(0, 0);
}

void Mouse(int button, int state, int x, int y)
{
	if (state != 0)
		return;

	mousex = x; mousey = windowHeight - y;
	//cout << mousex << " " << mousey << endl;
	if(!field.IsCheck)
	field.SetCellMatrix(mousex, mousey);

	if (!field.IsCheck && mousex >= windowWidth / 2 - 50 && mousex <= windowWidth / 2 + 50 && mousey >= 10 && mousey <= 40)
		field.CheckMatrix();
	else if (mousex >= 10 && mousex <= 40 && mousey <= 40 && mousey >= 10)
	{
		if (number > 1)
		{
			number--;
			LoadField();
		}
	}
	else if (mousex >= windowWidth - 40 && mousex <= windowWidth - 10 && mousey <= 40 && mousey >= 10)
	{
		if (number <= MaxValue)
		{
			number++;
			LoadField();
		}
	}

}

void Timer(int value) 
{
	glutPostRedisplay();
	glutTimerFunc(value, Timer, value);
}

int main(int argc, char** argv) 
{
	ShowWindow(hConsole, SW_HIDE);//собственно пр€чем оконо консоли
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("японский кроссворд");
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(60, Timer, 60);
	glutMouseFunc(Mouse);

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile("Base\\*.ini", &FindFileData);
	
	if (hFind != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(hFind, &FindFileData) != 0)
			MaxValue++;
	}

	if (MaxValue == 0) return 0;

	LoadField();

	glutMainLoop();
}
