#pragma once
#include "stdafx.h"
#include "personClass.h"
#include <fstream>

//THE LEADERBOARD CLASS
class leaderboard
{
public:
    person leader[11];
    person temp;
    int location;
    void readFile();
    void writeFile(GWindow &Gwin);
    void sort();
    void display(GWindow &Gwin);
};
