#include "connect4Class.h"

void connect4::setup(GWindow &Gwin)
{

	player[0].myColour = GwinColourNames::RED;
	player[0].myGo = true;
	player[1].myColour = GwinColourNames::BLUE; 
	player[1].myGo = false;

	Gwin.setPenColour(player[0].myColour);
	Gwin.writeText(10,10,"Enter Player 1's name: ");
	player[0].name = (Gwin.readString(12));
	player[0].fixName();

	Gwin.setPenColour(player[1].myColour);
	Gwin.writeText(10,20,"Enter Player 2's name: ");
	player[1].name = (Gwin.readString(12));
	player[1].fixName();

	Gwin.clear();

	Gwin.setPenColour(BLACK);
	Gwin.writeText(10,10,"Welcome to Connect4 ");

	player[0].writeName(Gwin);
	Gwin.setPenColour(BLACK);
	Gwin.writeText(" and ");
	player[1].writeName(Gwin);

	//game{

	int xleft=(Gwin.getWidth()-(gridSize*size)-20);
	int ytop=(Gwin.getHeight()-(size)-20);
	int xright=xleft+size;
	int ybottom=ytop+size;

	board[0].xLeft = xleft;
	int gridtop = Gwin.getHeight()-(20+(size*gridSize));
	for(int x=0;x<5;x++)//data to check for clicks
	{
		board[x+1].xLeft=board[x].xLeft+size;
		board[x].xRight = board[x+1].xLeft;
		board[x].yBottom = ybottom;
		board[x].yTop = gridtop;
	}

	for(int x=0;x<gridSize;x++)//data to draw coins
	{
		for(int i=0;i<gridSize;i++)
		{
			board[i].row[x].x = xleft+halfSize;
			board[i].row[x].y = ybottom-halfSize;
			xleft+=size;
			xright+=size;
		}
		ytop-=size;
		ybottom-=size;
		xleft=(Gwin.getWidth()-(gridSize*size)-20);
		xright=xleft+size;
	}
    //}reset
    //need to pull the board drawing and the data apart
    
    reset(Gwin);
}

int connect4::makeSelection(GWindow &Gwin)
{
	int column=-1;

	int x;
	int y;
	GMouseEvent c;
	while(column==-1 || !board[column].row[4].empty)
	{
		c = Mouse.waitEvent();
		x = c.x;
		y = c.y;
		if(c.isLeftDown())
		{
			if(x>board[0].xLeft && x<board[0].xRight && y>board[0].yTop && y<board[0].yBottom)
			{
				column = 0;
				break;
			}
			else if (x>board[1].xLeft && x<board[1].xRight && y>board[1].yTop && y<board[1].yBottom)
			{
				column = 1;
				break;
			}
			else if (x>board[2].xLeft && x<board[2].xRight && y>board[2].yTop && y<board[2].yBottom)
			{
				column = 2;
				break;
			}
			else if (x>board[3].xLeft && x<board[3].xRight && y>board[3].yTop && y<board[3].yBottom) 
			{
				column = 3;
				break;
			}
			else if(x>board[4].xLeft && x<board[4].xRight && y>board[4].yTop && y<board[4].yBottom)
			{
				column = 4;
				break;
			}
		}
	}

	moves++;

	person mover;
	mover = whosGo();
	Gwin.setPenColour(mover.myColour);
	
	player[0].myGo=!player[0].myGo;
	player[1].myGo=!player[1].myGo;

	for(int x=0;x<5;x++)
	{
		if(board[column].row[x].empty)
		{
			board[column].row[x].player = mover;
			Gwin.circle(board[column].row[x].x,board[column].row[x].y,halfSize);
			Gwin.refresh();
			board[column].row[x].empty = false;

			break;
		}
	}
	column++;
	return column;
}

bool connect4::won(GWindow &Gwin)
{
	for(int c=0;c<5;c++) //vertical
	{
		for(int x=0;x<2;x++)
		{
			if (board[c].row[x].player.name==player[0].name &&
				board[c].row[x+1].player.name==player[0].name &&
				board[c].row[x+2].player.name==player[0].name &&
				board[c].row[x+3].player.name==player[0].name)
			{
				winner = player[0];
				draw = false;
			}
			if (board[c].row[x].player.name==player[1].name &&
				board[c].row[x+1].player.name==player[1].name &&
				board[c].row[x+2].player.name==player[1].name &&
				board[c].row[x+3].player.name==player[1].name)
			{
				winner = player[1];
				draw = false;
			}
		}
	}

	for(int c=0;c<2;c++) //holizontal
	{
		for(int x=0;x<5;x++)
		{
			if (board[c].row[x].player.name==player[0].name &&
				board[c+1].row[x].player.name==player[0].name &&
				board[c+2].row[x].player.name==player[0].name &&
				board[c+3].row[x].player.name==player[0].name)
			{
				winner = player[0];
				draw = false;
			}
			if(board[c].row[x].player.name==player[1].name &&
				board[c+1].row[x].player.name==player[1].name &&
				board[c+2].row[x].player.name==player[1].name &&
				board[c+3].row[x].player.name==player[1].name)
			{
				winner = player[1];
				draw = false;
			}
		}
	}


	for(int x=0;x<2;x++)//diagonal downs (\)
	{ 
		for(int y=3;y<5;y++)
		{
			if(board[x].row[y].player.name==player[0].name &&
				board[x+1].row[y-1].player.name==player[0].name &&
				board[x+2].row[y-2].player.name==player[0].name &&
				board[x+3].row[y-3].player.name==player[0].name)
			{
				winner = player[0];
				draw = false;
			}
			if(board[x].row[y].player.name==player[1].name &&
				board[x+1].row[y-1].player.name==player[1].name &&
				board[x+2].row[y-2].player.name==player[1].name &&
				board[x+3].row[y-3].player.name==player[1].name)
			{
				winner = player[1];
				draw = false;
			}
		}
	}


	for(int x=0;x<2;x++)//diagonal up (/)
	{ 
		for(int y=0;y<2;y++)
		{
			if(board[x].row[y].player.name==player[0].name &&
				board[x+1].row[y+1].player.name==player[0].name&&
				board[x+2].row[y+2].player.name==player[0].name &&
				board[x+3].row[y+3].player.name==player[0].name)
			{
				winner = player[0];
				draw = false;
			}
			if(board[x].row[y].player.name==player[1].name &&
				board[x+1].row[y+1].player.name==player[1].name &&
				board[x+2].row[y+2].player.name==player[1].name &&
				board[x+3].row[y+3].player.name==player[1].name)
			{
				winner = player[1];
				draw = false;
			}
		}
	}

	if(draw==false)
	{
		Gwin.setPenColour(BLACK);
		Gwin.writeText(220,40,"Well done ");
		winner.writeName(Gwin);
		Gwin.setPenColour(BLACK);
		Gwin.writeText("! You won!");
		return true;
	}
	return false;
}

person connect4::whosGo()
{
	if (player[0].myGo)
		return player[0];
	else if (player[1].myGo)
		return player[1];
}

void connect4::reset(GWindow &Gwin)
{
    draw = true;
	moves = 0;
    
	for(int x=0;x<5;x++)
	{
		for(int y=0;y<5;y++)
		{
			board[x].row[y].empty=true;
		}
	}
    

    Gwin.setPenColour(BLACK);
    
	int xleft=(Gwin.getWidth()-(gridSize*size)-20);
	int ytop=(Gwin.getHeight()-(size)-20);
	int xright=xleft+size;
	int ybottom=ytop+size;
    
	for(int x=0;x<gridSize;x++)
	{
		for(int i=0;i<gridSize;i++)
		{
			Gwin.outlineRectangle(xleft,ytop,xright,ybottom);
			xleft+=size;
			xright+=size;
		}
		ytop-=size;
		ybottom-=size;
		xleft=(Gwin.getWidth()-(gridSize*size)-20);
		xright=xleft+size;
	}
	int numPlace=580;
	for(int i=5;i>0;i--)
	{
		Gwin.writeInt(numPlace,460,i);
		numPlace-=size;
	}
    
	Gwin.refresh();
    
}
