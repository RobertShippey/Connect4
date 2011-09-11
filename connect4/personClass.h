#pragma once
#include "stdafx.h"
#include <string>

class person
{
public:
    std::string name;
    GColour myColour;
	int moves;
    bool myGo;
    void writeName(GWindow &Gwin);
	void fixName();
};
