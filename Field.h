#pragma once
#include <vector>
#include <string>
#include "glut.h"

using namespace std;

class Field
{
	vector<vector<int>> HorisontNumbers;
	vector<vector<int>> VerticalNumbers;

	int NumberOfCellsW = 0;
	int NumberOfCellsH = 0;
	GLdouble UpperLeftCornerX = -160;
	GLdouble UpperLeftCornerY = 160;
	int GridSpacing = 40;
	bool** ControlMatrix = nullptr;
	bool** MatrixField = nullptr;
	string Name;

	void DrawHorisontNumber();
	void DrawVerticalNumber();

public:
	bool IsCheck = false;
	GLdouble WindowWidth = 0;
	GLdouble WindowHeight = 0;

	Field();
	void CheckMatrix();
	void DrawField();
	void LoadFile(string);
	void SetCellMatrix(int x, int y);
	void DeleteInfo();
	~Field();
};

