#pragma once

#ifndef _TABLE_H_
#define _TABLE_H_
#include <Windows.h>

template <class T>
class Table
{
	class Coord;

	int row;
	int column;

	Coord initCoord;
	Coord hiCoord;
	Coord deltaCoord;

	Coord static ConvCoord(Coord);

	Coord (*HiToAbs) (Coord);
	Coord (*AbsToHi) (Coord);

	bool isMathFunction;


public:
	Table();
	Table(int pRow, int pCol, Coord pInitCoord, Coord pHiCoord, Coord DeltaCoord);

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
	void setHiToAbs(Coord(*pFunc) (Coord));
	void setAbsToHi(Coord(*pFunc) (Coord));	

	int getRow();
	int getCol();
	Coord getInitCoord();
	Coord getDeltaCoord();
	Coord getHiCoord();

	~Table();
};

#endif