#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include "boardgen.h"
#include "engine.h"


FILE *saveFile;
WINDOW *board, *prompt, *title;
int maxx, maxy;
char menuList[3][20] = {"PLAY","SCORES", "EXIT"};


static char currPlayer = 'X';

void flipTurn(){
	if (currPlayer== 'X'){
		currPlayer = 'O';
	}
	else currPlayer = 'X';
}

void start(){
	initscr();
	curs_set(0);
	keypad(stdscr,TRUE);
}

void drawMenu(int choice){
	int i;
	for (i=0;i<3;i++){
		move(maxy/2+2*(i-1),(maxx - strlen(menuList[1]))/2);
		if (i==choice){
			attron(A_REVERSE);
			printw("%s",menuList[i]);
			attroff(A_REVERSE);
		}
		else{
			printw("%s",menuList[i]);
		}
	}
}

int startMenu(){
	int c, i;
	int choice=0;
	char *s = "PRESS ENTER TO SELECT YOUR OPTION";
	nodelay(stdscr, TRUE);
	drawMenu(choice);
	while(1){
		refresh();
		wrefresh(title);

		c = getch();
		if(c ==10 || c == ' ') break;
		if(c == KEY_DOWN){
			choice = (choice+1) %3;
			drawMenu(choice);
		}
		if(c == KEY_UP){
			choice = (choice+2) %3;
			drawMenu(choice);			
		}
		if(i < (int)strlen(s)){
			mvaddstr(maxy-1,maxx-1-i,s);
			napms(60);
			i++;
		}
		refresh();
	}
	return choice;
}

int main()
{
 
  int chosen;
  int temp,numRows, numCols,status;
  start();
  getmaxyx(stdscr, maxy, maxx);
  chosen = startMenu();
  

  switch(chosen) {
  case 0: /* play */
  	
  	nodelay(stdscr, FALSE);
  	clear();
  	echo();
  	curs_set(1);
  	mvprintw(2, maxx / 4, "-----INPUT DESIRED BOARD SIZE-----");
  	mvprintw(maxy / 4, maxx / 6, "PLESAE ENTER IN N[SPACE]M FORMAT");
  	mvprintw(maxy / 4+2,maxx/6,"MUST BE AT LEAST 4x4, IF SMALLER WILL AUTOMATICALLY BECOME 4x4");
  	mvprintw(maxy / 4+4, maxx / 6, "ENTER NUMBER OF ROWS: ");
  	status = scanw("%i",&numRows);

	while (status!=1){
		while((temp=scanw("%i")) !=EOF && temp!='\n');
		mvprintw(maxy / 4+8 ,maxx / 6,"Input Error:Please try again\n");
		move(maxy/4+4,maxx/6 +22);
		refresh();
		status = scanw("%i",&numRows);
	}
  	refresh();

  	mvprintw(maxy / 4+6, maxx / 6, "ENTER NUMBER OF COLS: ");
  	status = scanw("%i",&numCols);

	while (status!=1){
		while((temp=getchar()) !=EOF && temp!='\n');
		mvprintw(maxy / 4+8 ,maxx / 6,"Input Error:Please try again\n");
		move(maxy/4+6,maxx/6 +22);
		refresh();
		status = scanw("%i",&numCols);
	}

	if (numCols < 4){
		numCols =4;
	}
	if(numRows < 4){
		numRows =4;
	}

	BOARD *mainBoard;
	mainBoard = newBoard(numRows,numCols);
	printBoard(mainBoard);


	for (;;)
	{

		int move,x,y;
		printw("Player %c Where would you like to insert?\n",currPlayer);
		scanw("%i",&move);
		refresh();

		if(boardFull(mainBoard)){
			getyx(stdscr,y,x);
			mvprintw(y+1,x-x,"Cannot fit any more pieces in board.");
			refresh();
			getch();
			endwin();
			exit(0);
		}
		insertPiece(mainBoard,move,currPlayer);
		if(checkWin(mainBoard, currPlayer)){
			getyx(stdscr,y,x);
			mvprintw(y+1,x-x,"Player %c has won!\nPress Enter to Exit",currPlayer);
			refresh();
			getch();
			endwin();
			exit(0);
		}
		flipTurn();

	}



    break;
  

  case 1: /* check scores*/
 
    break;
  case 2: /* Quit */
    getch();
    endwin();
 	exit(0);
    break;
  default:
    break;
  }
	endwin();
	return 1;
}
