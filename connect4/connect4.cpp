// connect4.cpp : Defines the entry point for the application.
// Author: Robert Shippey
// ID: N0305434
// Version: 0.1
// Date: 14 Apr 2011
// Description: Connect4

#include "stdafx.h"
#include "connect4.h"

int main ()
{
    
    GWindow Gwin;
	Gwin.setTitle("Connect4 by Robert Shippey (N0305434)");
	Gwin.clear();
	Gwin.showDebugOverlay(false);
	
    
    connect4 game;
    game.setup(Gwin);
    
	int yText=30; 
    
	//beginning of game loop
	for(int x=0;x<25;x++)
	{
        Gwin.writeText(10,yText," ");
		game.whosGo().writeName(Gwin);
        Gwin.writeText(", click a column! ");
		Gwin.refresh();
		game.makeSelection(Gwin);
		Gwin.writeInt(tehAnswer);
		yText+=10;
        
        
		if(game.won(Gwin))
		{
            break;
        }

	} //end of game loop
    
	Gwin.refresh();
    
    leaderboard scorez;
	
    scorez.readFile();
    
	Gwin.writeText("."); Gwin.refresh();
    
	if(game.draw) //is game a draw?
	{
		Gwin.setPenColour(BLACK);
		Gwin.writeText(220,40,"The game was a draw!");
		 scorez.leader[10].name = "===";
        scorez.leader[10].moves = 888;
	}
	else
	{ 
        scorez.leader[10].name = game.winner.name;
        scorez.leader[10].moves = game.moves;
	}
	
    scorez.sort();
	scorez.writeFile(Gwin);
    
	Gwin.writeText(". Type 1 for leaderboard or 0 to quit: ");
	if(Gwin.readInt()==0)
	{
        return 0;
    }
	
    Gwin.clear();
	
    scorez.display(Gwin);
    
	scorez.location+=20;
	Gwin.writeText(30, scorez.location, "Press any key to quit");
	Gwin.refresh();
    
	// Finally, wait for a key to be pressed
	Keyboard.waitKey();	
	return 0;
    
}
