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

template <class T, class... Other>
class Table
{
	typedef tuple<T, Other...> TTuple;
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
	Table(int pRow, Coord pInitCoord, Coord pInitHiCoord, Coord pDeltaCoord, vector<string> pColNames);

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

template <class T, class... Other>
Table<T, Other...>::Table(int pRow, Coord pInitCoord, Coord pInitHiCoord, Coord pDeltaCoord, vector<string> pColNames) :
row(pRow),
initCoord(pInitCoord),
hiCoord(pInitHiCoord),
deltaCoord(pDeltaCoord),
initHiCoord(pInitHiCoord),
isMathFunction(false)
{
	column = sizeof...(Other)+1;
	if (column == 2)
		isMathFunction = true;

	colNames = pColNames;
}

template <class T, class... Other>
Table<T, Other...>::Table()
{
	Table(1, 1, { 0, 0 }, { 0, 0 }, { 0, 0 });
}

template <class T, class... Other>
Table<T, Other...>::~Table()
{
};

//==============================
// SETTING DATA MEMBER
//==============================
template <class T, class... Other>
void Table<T, Other...>::setRow(int pRow)
{
	this->row = pRow;
}

template <class T, class... Other>
void Table<T, Other...>::setCol(int pCol)
{
	this->column = pCol;
}

template <class T, class... Other>
void Table<T, Other...>::setInitCoord(Coord pCoord)
{
	this->initCoord = pCoord;
}

template <class T, class... Other>
void Table<T, Other...>::setDeltaCoord(Coord pCoord)
{
	this->deltaCoord = pCoord;
}

template <class T, class... Other>
void Table<T, Other...>::setHiCoord(Coord pCoord)
{
	this->hiCoord = pCoord;
}

template <class T, class... Other>
void Table<T, Other...>::setInitHiCoord(Coord pCoord)
{
	this->initHiCoord = pCoord;
}

template <class T, class... Other>
int Table<T, Other...>::getRow()
{
	return row;
}

template <class T, class... Other>
int Table<T, Other...>::getCol()
{
	return column;
}

//==============================
// GETTING DATA MEMBER
//==============================
template <class T, class... Other>
Table<T, Other...>::template Coord Table<T, Other...>::getInitCoord()
{
	return initCoord;
}

template <class T, class... Other>
Table<T, Other...>::template Coord Table<T, Other...>::getDeltaCoord()
{
	return deltaCoord;
}

template <class T, class... Other>
Table<T, Other...>::template Coord Table<T, Other...>::getHiCoord()
{
	return hiCoord;
}

template <class T, class... Other>
Table<T, Other...>::template Coord Table<T, Other...>::getInitHiCoord()
{
	return ìnitHiCoord;
}

//=================================
// STATIC WINDOW CURSOR FUNCTIONS
//=================================

template <class T, class... Other>
void static Table<T, Other...>::gotoxy(int column = wherex(), int line = wherey())
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
		);
}

template <class T, class... Other>
int static Table<T, Other...>::wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
		))
		return -1;
	return csbi.dwCursorPosition.Y;
}

template <class T, class... Other>
int static Table<T, Other...>::wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
		))
		return -1;
	return csbi.dwCursorPosition.Y;
}

//==============================
// OTHER FUNCTIONS
//==============================

template <class T, class... Other>
Table<T, Other...>::template Coord Table<T, Other...>::HiToAbs(Coord pCoord)
{
	Coord rCoord = { 0, 0 };

	rCoord.x = pCoord.x - getInitHiCoord().x;
	rCoord.x /= getDeltaCoord().x;

	rCoord.y = pCoord.y - getInitHiCoord().y;
	rCoord.y /= getDeltaCoord().y;

	return rCoord;
}

template <class T, class... Other>
Table<T, Other...>::template Coord Table<T, Other...>::AbsToHi(Coord pCoord)
{
	Coord rCoord = { 0, 0 };

	rCoord.x = getDeltaCoord().x * pCoord.x + getInitHiCoord().x;

	rCoord.y = getDeltaCoord().y * pCoord.y + getInitHiCoord().y;
	return rCoord;
}

template <class T, class... Other>
void Table<T, Other...>::hilight(Coord crd, int length)
{
	WORD fore = FOREGROUND_BLUE;
	WORD back = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;

	COORD cord;
	DWORD wrd;
	cord.X = crd.x;
	cord.Y = crd.y;

	FillConsoleOutputAttribute(Global::hStdout, fore | back, length, cord, &wrd);

	//cout << endl;
	//cout << wrd;
}

template <class T, class... Other>
void Table<T, Other...>::delight(Coord crd, int length)
{
	WORD fore = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	COORD cord;
	DWORD wrd;
	cord.X = crd.x;
	cord.Y = crd.y;

	FillConsoleOutputAttribute(Global::hStdout, fore, length, cord, &wrd);

	//cout << endl;
	//cout << wrd;
}

template <class T, class... Other>
void Table<T, Other...>::drawTable()
{
	gotoxy();
}
#endif