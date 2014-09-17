#pragma once

#ifndef _TABLE_H_
#define _TABLE_H_

#include <Windows.h>
#include <string>
#include <vector>
#include <tuple>

using std::string;
using std::vector;
using std::tuple;

template <class... T>
class Table
{
	typedef tuple<&T> TTuple;
	typedef vector<TTuple> TVector2D;
	class Coord;

	int row;
	int column;

	vector<string> colNames;
	TVector2D tableData;

	Coord initCoord;
	Coord initHiCoord;
	Coord hiCoord;
	Coord deltaCoord;

	Coord static ConvCoord(Coord);

	Coord HiToAbs (Coord);
	Coord AbsToHi (Coord);

	bool isMathFunction;

	void static gotoxy(int column = wherex(), int line = wherey());
	int static wherex();
	int static wherey();

public:
	Table();
	Table(int pRow, int pCol, Coord pInitCoord, Coord pHiCoord, Coord pInitHiCoord, Coord pDeltaCoord, vector<string> pColNames);

	class Coord
	{
	public:
		int x;
		int y;

		Coord()
		{
			x = 0;
			y = 0;
		};

		Coord(int X, int Y)
		{
			x = X;
			y = Y;
		}

		bool operator== (Coord p_Coord)
		{
			return (p_Coord.x == this->x) && (p_Coord.y == this->y);
		}

		bool operator!= (Coord p_Coord)
		{
			return (p_Coord.x != this->x) && (p_Coord.y != this->y);
		}
	};

	void hilight(Coord crd, int length);
	void delight(Coord crd, int length);

	void setRow(int pRow);
	void setCol(int pCol);
	void setInitCoord(Coord pCoord);
	void setDeltaCoord(Coord pCoord);
	void setHiCoord(Coord pCoord);
	void setInitHiCoord(Coord pCoord);

	int getRow();
	int getCol();
	Coord getInitCoord();
	Coord getDeltaCoord();
	Coord getHiCoord();
	Coord getInitHiCoord();

	void drawTable();

	~Table();
};

#endif