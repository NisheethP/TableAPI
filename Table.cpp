#include "Table.h"

template <class T>
Table<T>::Table(int pRow, int pCol, Coord pInitCoord, Coord pHiCoord, Coord DeltaCoord) : 
row(pRow), 
column(pCol),
initCoord(pInitCoord),
hiCoord(pHiCoord),
deltaCoord(pDeltaCoord),
isMathFunction(false)
{
	if (column == 2)
		isMathFunction = true;
	HiToAbs = &(ConvCoord);
	AbsToHigh = &(ConvCoord);
}

template <class T>
Table<T>::~Table()
{
};

//==============================
// SETTING DATA MEMBER
//==============================
template <class T>
void Table<T>::setRow(int pRow)
{
	this->row = pRow;
}

template <class T>
void Table<T>::setCol(int pCol)
{
	this->column = pCol;
}

template <class T>
void Table<T>::setInitCoord(Coord pCoord)
{
	this->initCoord = pCoord;
}

template <class T>
void Table<T>::setDeltaCoord(Coord pCoord)
{
	this->deltaCoord = pCoord;
}

template <class T>
void Table<T>::setHiCoord(Coord pCoord)
{
	this->hiCoord = pCoord;
}

template <class T>
void Table<T>::setHiToAbs(Coord(*pFunc) (Coord))
{
	this->HiToAbs = pFunc;
}

template <class T>
void Table<T>::setAbsToHi(Coord(*pFunc) (Coord))
{
	this->AbsToHi = pFunc;
}

template <class T>
int Table<T>::getRow()
{
	return row;
}

template <class T>
int Table<T>::getCol()
{
	return column;
}

//==============================
// GETTING DATA MEMBER
//==============================
template <class T>
Table<T>::template Coord Table<T>::getInitCoord()
{
	return initCoord;
}

template <class T>
Table<T>::template Coord Table<T>::getDeltaCoord()
{
	return deltaCoord;
}

template <class T>
Table<T>::template Coord Table<T>::getHiCoord()
{
	return hiCoord;
}

//==============================
// OTHER FUNCTIONS
//==============================

template <class T>
Table<T>::template Coord static Table<T>::ConvCoord(Coord pCoord)
{
	return pCoord;
}

template <class T>
void Table<T>::hilight(Coord crd, int length)
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

template <class T>
void Table<T>::delight(Coord crd, int length)
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