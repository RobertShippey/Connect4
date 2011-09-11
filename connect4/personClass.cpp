#include "personClass.h"

void person::writeName(GWindow &Gwin)
{
    Gwin.setPenColour(myColour);
    Gwin.writeString(name);
}

void person::fixName()
{
	std::string space = (" ");
	std::string score = ("_");
	size_t found = -1;
	int length = name.length();
	for(int x=0;x<length;x++)
	{
		found=name.find(space);
		if(found!=-1)
		{
			name.replace(found, 1, score);
		}
	}
}