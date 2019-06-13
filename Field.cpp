#include <iostream>
#include <fstream>
#include "Field.h"
#include "DrawNumber.h"
#include "Point.h"
#include "glut.h"

using namespace std;

Field::Field()
{
	/*NumberOfCells = 10;

	HorisontNumbers.resize(10);
	HorisontNumbers[0] = { 2, 4 };
	HorisontNumbers[1] = { 1, 7 };
	HorisontNumbers[2] = { 1, 3, 1 };
	HorisontNumbers[3] = { 3, 2 };
	HorisontNumbers[4] = { 5 };
	HorisontNumbers[5] = { 5 };
	HorisontNumbers[6] = { 2, 3 };
	HorisontNumbers[7] = { 1, 2, 2 };
	HorisontNumbers[8] = { 1, 1 };
	HorisontNumbers[9] = { 3, 1 };

	VerticalNumbers.resize(10);
	VerticalNumbers[0] = { 3, 3 };
	VerticalNumbers[1] = { 1, 1 };
	VerticalNumbers[2] = { 1, 2, 1 };
	VerticalNumbers[3] = { 2, 4 };
	VerticalNumbers[4] = { 4 };
	VerticalNumbers[5] = { 6 };
	VerticalNumbers[6] = { 2, 2 };
	VerticalNumbers[7] = { 1, 4, 1 };
	VerticalNumbers[8] = { 8 };
	VerticalNumbers[9] = { 4 };*/
}

void Field::LoadFile(string p)
{
	ifstream read("Base/" + p);
	if (!read.is_open())
		return;
	read >> NumberOfCellsW >> NumberOfCellsH;

	MatrixField = new bool* [NumberOfCellsH];
	for (int i = 0; i < NumberOfCellsH; i++)
	{
		MatrixField[i] = new bool[NumberOfCellsW];
		for (int j = 0; j < NumberOfCellsW; j++)
			MatrixField[i][j] = false;
	}

	ControlMatrix = new bool* [NumberOfCellsH];
	for (int i = 0; i < NumberOfCellsH; i++)
		ControlMatrix[i] = new bool[NumberOfCellsW];

	for (int i = 0; i < NumberOfCellsH; i++)
		for (int j = 0; j < NumberOfCellsW; j++)
			read >> ControlMatrix[i][j];

	read.ignore();
	getline(read, Name);

	HorisontNumbers.resize(NumberOfCellsH);
	VerticalNumbers.resize(NumberOfCellsW);
	int maxH = 0, maxV = 0;

	for (int i = 0; i < NumberOfCellsH; i++)
	{
		int count = 0;
		for (int j = 0; j < NumberOfCellsW; j++)
		{
			if (ControlMatrix[i][j]) 
				count++;
			else if (count != 0)
			{
				HorisontNumbers[i].push_back(count);
				count = 0;
			}
		}

		if (count != 0)
		{
			HorisontNumbers[i].push_back(count);
			count = 0;
		}
		if (HorisontNumbers[i].size() > maxH)
			maxH = HorisontNumbers[i].size();
	}

	for (int j = 0; j < NumberOfCellsW; j++)
	{
		int count = 0;
		for (int i = 0; i < NumberOfCellsH; i++)
		{
			if (ControlMatrix[i][j])
				count++;
			else if (count != 0)
			{
				VerticalNumbers[j].push_back(count);
				count = 0;
			}
		}

		if (count != 0)
		{
			VerticalNumbers[j].push_back(count);
			count = 0;
		}
		if (VerticalNumbers[j].size() > maxV)
			maxV = VerticalNumbers[j].size();
	}

	UpperLeftCornerX = maxH * 25 + 5;
	UpperLeftCornerY = NumberOfCellsH * GridSpacing + 80;
	
	WindowWidth = maxH * 30 + NumberOfCellsW * GridSpacing + 10;
	WindowHeight = maxV * 32 + NumberOfCellsH * GridSpacing + 100 + 5;
}

void Field::DrawHorisontNumber()
{
	if (HorisontNumbers.size() == 0) return;
	int len1 = HorisontNumbers.size();

	for (int i = 0; i < len1; i++)
	{
		int len2 = HorisontNumbers[i].size();
		for (int j = 0; j < len2; j++)
			DrawNumber('0' + HorisontNumbers[i][j], point(double(UpperLeftCornerX - (len2 - j) * 25), double(UpperLeftCornerY - 3 - i * 40)));
	}
}

void Field::DrawVerticalNumber()
{
	if (VerticalNumbers.size() == 0) return;
	int len1 = VerticalNumbers.size();
	for (int i = 0; i < VerticalNumbers.size(); i++)
	{
		int len2 = VerticalNumbers[i].size();
		for (int j = 0; j < len2; j++)
			DrawNumber('0' + VerticalNumbers[i][len2 - j - 1], point((UpperLeftCornerX + 12 + i * 40), (UpperLeftCornerY + (j + 1) * 38)));
	}
}

void DrawRectangle(point p1, point p2)
{
	glBegin(GL_QUADS);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p1.x, p2.y);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p2.x, p1.y);
	glEnd();
}

void Field::DrawField()
{
	for (int i = 0; i <= NumberOfCellsW; i++)
	{
		glBegin(GL_LINES);
		glVertex2d(UpperLeftCornerX + (i * GridSpacing), UpperLeftCornerY);
		glVertex2d(UpperLeftCornerX + (i * GridSpacing), UpperLeftCornerY - (NumberOfCellsH * GridSpacing));
		glEnd();
	}

	for (int i = 0; i <= NumberOfCellsH; i++)
	{
		glBegin(GL_LINES);
		glVertex2d(UpperLeftCornerX, UpperLeftCornerY - (i * GridSpacing));
		glVertex2d(UpperLeftCornerX + (NumberOfCellsW * GridSpacing), UpperLeftCornerY - (i * GridSpacing));
		glEnd();
	}

	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex2d(UpperLeftCornerX + (NumberOfCellsW / 2 * GridSpacing), UpperLeftCornerY);
	glVertex2d(UpperLeftCornerX + (NumberOfCellsW / 2 * GridSpacing), UpperLeftCornerY - (NumberOfCellsH * GridSpacing));
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(UpperLeftCornerX, UpperLeftCornerY - (NumberOfCellsH / 2 * GridSpacing));
	glVertex2d(UpperLeftCornerX + (NumberOfCellsW * GridSpacing), UpperLeftCornerY - (NumberOfCellsH / 2 * GridSpacing));
	glEnd();
	glLineWidth(2);

	DrawHorisontNumber();
	DrawVerticalNumber();

	for(int i = 0; i < NumberOfCellsH; i++)
		for (int j = 0; j < NumberOfCellsW; j++)
		{
			if (!MatrixField[i][j]) continue;
			DrawRectangle(point(UpperLeftCornerX + (j * GridSpacing), UpperLeftCornerY - i * GridSpacing), point(UpperLeftCornerX + ((j + 1) * GridSpacing), UpperLeftCornerY - ((i + 1) * GridSpacing)));
		}

	if (IsCheck)
	{
		point p1, p2;
		p1.x = 0; p1.y = WindowHeight/2 + 20;
		p2.x = WindowWidth; p2.y = WindowHeight/2 - 20;

		glColor3d(0, 1, 0);
		glBegin(GL_QUADS);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p1.x, p2.y);
		glVertex2d(p2.x, p2.y);
		glVertex2d(p2.x, p1.y);
		glEnd();

		glColor3d(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2d(p1.x, p1.y);
		glVertex2d(p1.x, p2.y);
		glVertex2d(p2.x, p2.y);
		glVertex2d(p2.x, p1.y);
		glEnd();

		glColor3d(0, 0, 0);
		glRasterPos2i(WindowWidth / 2 - Name.size()*9/2, WindowHeight / 2 - 5); //позиция текста
		for (int i = 0; i < Name.size(); i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, Name[i]);
	}
}

void Field::SetCellMatrix(int x, int y)
{
	if (x >= UpperLeftCornerX && x <= UpperLeftCornerX + (NumberOfCellsW * GridSpacing) && y <= UpperLeftCornerY && y >= UpperLeftCornerY - (NumberOfCellsH * GridSpacing))
	{
		int IndexX = floorf(abs(y - UpperLeftCornerY) / GridSpacing);
		int IndexY = floorf(abs(x - UpperLeftCornerX) / GridSpacing);
		MatrixField[IndexX][IndexY] = !MatrixField[IndexX][IndexY];
	}
}

void Field::CheckMatrix()
{
	bool check = true;
	for(int i = 0; i < NumberOfCellsH; i++)
		for(int j = 0; j < NumberOfCellsW; j++)
			if (MatrixField[i][j] != ControlMatrix[i][j])
			{
				check = false;
				break;
			}

	IsCheck = check;
}

void Field::DeleteInfo()
{
	if (ControlMatrix != nullptr)
	{
		for (int i = 0; i < NumberOfCellsH; i++)
			delete[] ControlMatrix[i];
		delete[] ControlMatrix;
	}

	if (MatrixField != nullptr)
	{
		for (int i = 0; i < NumberOfCellsH; i++)
			delete[] MatrixField[i];
		delete[] MatrixField;
	}

	VerticalNumbers.clear();
	HorisontNumbers.clear();
	NumberOfCellsH = NumberOfCellsW = 0;
	UpperLeftCornerX = UpperLeftCornerY = 0;
	IsCheck = false;
	Name = "";
}

Field::~Field()
{
}
