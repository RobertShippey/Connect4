#pragma once
#include "stdafx.h"
#include "personClass.h"

//constants
const int size = 80; //size of the square
const int halfSize = size/2; //needed for many calculations
const int gridSize = 5; //grid height in squares

class cell
{
public:
    person player;
    bool empty;
    int x;
    int y;
};

class column
{
public:
	cell row[5];
	int xLeft, xRight, yTop, yBottom;
};

//THE GAME CLASS
class connect4
{
public:
    column board[5];
    person player[2];
    person winner;
	int moves;
    bool draw;
    void setup(GWindow &Gwin);
	void reset(GWindow &Gwin);
    int makeSelection(GWindow &Gwin);
    bool won(GWindow &Gwin);
	person whosGo();
    
};
