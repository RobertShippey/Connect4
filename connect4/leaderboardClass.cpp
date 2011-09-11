#include "leaderboardClass.h"

void leaderboard::readFile()
{
    std::ifstream readBoard;
	readBoard.open("scores.txt");
    if(readBoard)
    {
        for(int x=0;x<10;x++)
        {
            if(!readBoard.eof())
            {
                readBoard>>leader[x].name;
                readBoard>>leader[x].moves;
            }
        }
    }
	else
    { //if the file doesn't exist, make one with sample data
        std::ofstream sampleData("scores.txt");	
        for(int x=0;x<10;x++)
        { 
            sampleData << "===" << " " << "888" << "\n";
			leader[x].name = "===";
			leader[x].moves = 888;
        }
        sampleData.close();
    }
}


void leaderboard::sort()
{
    //Bubble sort the winners leaderboard
	person temp;
	for (int i=10; i>0; i--)
	{
		for (int j=0; j<i; j++)
		{
			if (leader[j].moves>leader[j+1].moves)
			{
				temp = leader[j];
				leader[j] = leader[j+1];
				leader[j+1]= temp;
			}
		}
	}
}

void leaderboard::writeFile(GWindow &Gwin)
{
    std::ofstream writeBoard;
	writeBoard.open("scores.txt");	
	for(int j=0;j<10;j++)
	{ 
		writeBoard << leader[j].name << " " << leader[j].moves << "\n";
		Gwin.writeText("."); Gwin.refresh();
	}
	writeBoard.close();
}

void leaderboard::display(GWindow &Gwin)
{
    location = 50;
	Gwin.setPenColour(BLACK);
	Gwin.writeText(20,20,"Thank you for playing Connect4! Here is the leaderboard:");
	Gwin.writeText(20,35, "Name"); Gwin.writeText(20,36, "_____");
	Gwin.writeText(100, 35, "No. of turns");
	Gwin.writeText(100, 36, "____________");
	for(int x=0;x<10;x++)
	{
		Gwin.writeString(20,location, leader[x].name);
		Gwin.writeInt(100, location, leader[x].moves);
		location+=10;
	}
    Gwin.refresh();
}