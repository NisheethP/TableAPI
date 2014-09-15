#include "Table.h"

template <class T>
Table<T>::Table(int pRow, int pCol) : row(pRow), column(pCol)
{
	if (column == 2)
		isMathFunction = true;
}

template <class T>
Table<T>::~Table()
{
}

template <class T>
void Table<T>::hilight(Coord crd, int length)
{
	WORD fore = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
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