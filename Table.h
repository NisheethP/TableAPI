#pragma once

#ifndef _TABLE_H_
#define _TABLE_H_

#include <Windows.h>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <type_traits>
#include <boost\utility\value_init.hpp>
#include <boost\any.hpp>

using std::string;
using std::vector;
using std::tuple;
using std::cout;

//==============================
// CLASS DECLERATION
//==============================

template <class T, class... Other>
class Table
{
	//Defining of data types
	typedef tuple<T, Other...> TTuple;
	typedef vector<TTuple> TVector2D;
	typedef vector<string> StrVector;
	class Coord;

	static int MAX_ROW;
	int row;
	int column;

	StrVector colNames;
	TVector2D tableData;

	Coord initCoord;
	Coord initHiCoord;
	Coord hiCoord;
	Coord deltaCoord;

	Coord static ConvCoord(Coord);
	
	void gotoxy(int column = wherex(), int line = wherey());
	int static wherex();
	int static wherey();
	bool isOdd(int x) { return (x % 2) ? true : false; }
	int strMid(string);

public:
	Table();
	Table(int pRow, Coord pInitCoord, Coord pInitHiCoord, Coord pDeltaCoord);

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

	void hilight(Coord , int );
	void delight(Coord , int );

	void setRow(int);
	void setCol(int);
	void setInitCoord(Coord);
	void setDeltaCoord(Coord);
	void setHiCoord(Coord);
	void setInitHiCoord(Coord);
	void setColNames(StrVector);
	boost::any getTableTerm(int, int);

	int getRow();
	int getCol();
	Coord getInitCoord();
	Coord getDeltaCoord();
	Coord getHiCoord();
	Coord getInitHiCoord();
	StrVector getColNames();

	void drawTable();

	Coord HiToAbs(Coord);
	Coord AbsToHi(Coord);

	~Table();
};

//==============================
// STATIC CLASS MEMBERS
//==============================
template <class T, class... Other>
int Table<T, Other...>::MAX_ROW = 25;

//==============================
// CLASS FUNCTIONS
//==============================

template <class T, class... Other>
Table<T, Other...>::Table(int pRow, Coord pInitCoord, Coord pInitHiCoord, Coord pDeltaCoord) :
row(pRow),
initCoord(pInitCoord),
hiCoord(pInitHiCoord),
deltaCoord(pDeltaCoord),
initHiCoord(pInitHiCoord)
{
	/*
	 *Its is too complicated to make a general method to iterate over
	 *a tuple at runtime (can't determine the return type at runtime for a variable)
	 *So, I am hard-coding it to take only MAX_ROW (25) rows. If I ever feel the need to use
	 *more rows, 'drawTable()' can be updated to handle more rows.
	 *Just need to add:
	 *    cout << std::get<ROW_NUMBER> (tableData);
	 *after the case statement for that row
	 */
	if (row > MAX_ROW)
		row = MAX_ROW;
	boost::value_initialized<tuple<T, Other...>> initTuple;

	column = sizeof...(Other)+1;
	for (int i = 0; i < column; ++i)
		colNames.push_back("");

	tuple<T, Other...> var;
	for (int rowIter = 0; rowIter < row; ++rowIter)
	{
		for (int colIter = 0; colIter < column; ++colIter)
		{
			tableData.push_back(initTuple);
		}
	}	
}

template <class T, class... Other>
Table<T, Other...>::Table()
{
	Table(1, { 0, 0 }, { 0, 0 }, { 0, 0 });
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

template <class T, class... Other>
void Table<T, Other...>::setColNames(StrVector pColNames)
{
	colNames = pColNames;
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

template <class T, class... Other>
Table<T, Other...>::template StrVector Table<T, Other...>::getColNames()
{
	return colNames;
}

//=================================
//WINDOW CURSOR FUNCTIONS
//=================================

template <class T, class... Other>
void Table<T, Other...>::gotoxy(int column = wherex(), int line = wherey())
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
int Table<T, Other...>::strMid(string str)
{
		return (int)(str.length()) * 0.5f;
}


//==============================
// TABLE INTERACTION
//==============================
template <class T, class... Other>
void Table<T, Other...>::drawTable()
{
	int colDividers = column - 1;

	gotoxy(initCoord.x, initCoord.y);
	Coord curCoord = { initCoord.x - deltaCoord.x, initCoord.y };
	
	/*
	 *This section outputs the first row of the table.
	 *It consists of the names of the columns and the first dividers.
	 *The individual 'cout' is to output a vertical bar (|) for the
	 *divider line that separates row numbers
	 */
	
	gotoxy(curCoord.x, curCoord.y);
	cout << "|";

	int colNameIter = 0;
	
	for (int colIter = 0; colIter < colDividers + column ; ++colIter)
	{
		curCoord = { initCoord.x + colIter * deltaCoord.x, initCoord.y };

		gotoxy(curCoord.x, curCoord.y);
		if (isOdd(colIter))
			cout << "|";
		else
		{
			string str = colNames[colNameIter++];
			curCoord.x -= strMid(str);
			gotoxy(curCoord.x, curCoord.y);
			cout << str;
		}		
	}

	/*
	 *This prints the second row of the table.
	 *This just outputs a series of '-' in a line
	 *to divide the column names from the entries.
	 *It outputs a '+' at every location that has
	 *a vertical bar (|) in the above and below
	 *row.
	 */

	curCoord = { initCoord.x - deltaCoord.x - 3, initCoord.y + 1 };
	gotoxy(curCoord.x, curCoord.y);
	for (int i = 0; i < 3; ++i)
		cout << "-";

	curCoord = { initCoord.x - deltaCoord.x, initCoord.y + 1};

	for (int i = 0; i < deltaCoord.x * (column + 2); ++i)
	{
		gotoxy(curCoord.x + i, curCoord.y);
		if (i % (2*deltaCoord.x) != 0)
			cout << "-";
		else
			cout << "+";
	}

	/*
	 *This will output the various rows.
	 *Tuple needs to be created to get a variable of
	 *each type in Parameter Pack. The default garbage value is used.
	 */
	tuple<T, Other...> templTuple;
	int rowDataIter = 0;
	int colDataIter = 0;

	for (int rowIter = 0; rowIter < row * deltaCoord.y; ++rowIter)
	{
		for (int colIter = 0; colIter < column * deltaCoord.x; ++colIter)
		{
			curCoord = { initCoord.x + 2*(deltaCoord.x*colIter), initCoord.y + deltaCoord.y*rowIter + 2 };

			gotoxy(curCoord.x - 2*deltaCoord.x + 2, curCoord.y);
			if (colIter == 0)
				cout << rowIter + 1;
			else if (colIter % (2*deltaCoord.x) == 0)
				cout << "|";
			else
			{
				/*
				 *As switch-case won't go to any value greater than colDataIter
				 *I don't need to add the check for if the column is within limit of the tuple.
				 *But, just as a failsafe, I will put the whole case inside an if statement checking that
				 *colDataIter is within safe limits.
				 */

				
				if (colDataIter < column)
					++colDataIter;
			}
		}
		if (rowDataIter < row)
			++rowDataIter;
	}
}

template <class T, class... Other>
boost::any Table<T, Other...>::getTableTerm(int row, int col)
{
	if (col < column && col == 0)
		return std::get<0>(tableData[row]);
	if (col < column && col == 0)
		return std::get<0>(tableData[row]);
	if (col < column && col == 0)
		return std::get<0>(tableData[row]);
	if (col < column && col == 0)
		return std::get<0>(tableData[row]);
	if (col < column && col == 0)
		return std::get<0>(tableData[row]);
	if (col < column && col == 0)
		return std::get<0>(tableData[row]);
	if (col < column && col == 0)
		return std::get<0>(tableData[row]);
	if (col < column && col == 0)
		return std::get<0>(tableData[row]);
}
#endif