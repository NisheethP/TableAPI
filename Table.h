#pragma once

#ifndef _TABLE_H_
#define _TABLE_H_
#include <Windows.h>

#ifndef _COORD_
#define _COORDS_



#endif

template <class T>
class Table
{
	class Coord;

	int row;
	int column;

	Coord initCoord;
	Coord hiCoord;
	Coord deltaCoord;

	Coord (*HiToAbs) (Coord);
	Coord (*AbsToHi) (Coord);

	bool isMathFunction;


public:
	Table();

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

		Coord(Coord pCoord)
		{
			this->x = pCoord.x;
			this->y = pCoord.y;
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
	void setHiToAbs(Coord(*pFunc) (Coord));
	void setAbsToHi(Coord(*pFunc) (Coord));

	int getRow();
	int getCol();
	Coord getInitCoord();
	Coord getDeltaCoord();

	~Table();
};

#endif