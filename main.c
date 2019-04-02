#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include "boardgen.h"


FILE *saveFile;
WINDOW *board, *prompt, *title;
int maxx, maxy, move1 =0;
char menuList[5][20] = {"2 PLAYER","SOLO VS COMPUTER","SCORES","CLEAR SCORES", "EXIT"};


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
	mvprintw(maxy/4,maxx/6,"Welcome to Connect4!");
	mvprintw(maxy/4+1,maxx/6,"This program was created by Andrew Poteres");

	for (i=0;i<5;i++){
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
			choice = (choice+1) %5;
			drawMenu(choice);
		}
		if(c == KEY_UP){
			choice = (choice+4) %5;
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

void writeWinner(char currPlayer){
	saveFile = fopen("scores.bin","r+");
	if(currPlayer =='X'){
		int x;
		fseek(saveFile,0,SEEK_SET);
		fscanf(saveFile,"%3i",&x);
		x++;
		fseek(saveFile,0,SEEK_SET);
		fprintf(saveFile,"%3i\n",x);
		fclose(saveFile);
	}
	else{
		int x;
		fseek(saveFile,4,SEEK_SET);
		fscanf(saveFile,"%3i",&x);
		x++;
		fseek(saveFile,4,SEEK_SET);
		fprintf(saveFile,"%3i\n",x);
		fclose(saveFile);
	}
}

void eraseScores(){
	int status;
	status = (remove("scores.bin"));

	if (status == 0){//file deleted
		saveFile = fopen("scores.bin","w+");
		fprintf(saveFile,"  0\n");
		fprintf(saveFile,"  0\n");
	}
	else{
		saveFile = fopen("scores.bin","w");
		fprintf(saveFile,"  0\n");
		fprintf(saveFile,"  0\n");
	}
	fclose(saveFile);
	mvprintw(maxy-1,0,"Scores Succesfully Erased");
	refresh();
}

int valid(BOARD *brd, int move){
	//make sure not full
	if(boardFull(brd)){
		printw("Cannot fit any more pieces in board. Result is draw\n");
		printw("Press ENTER to exit\n");
		refresh();
		getch();
		endwin();
		exit(0);
	}
	//make sure valid column
	if (move <= 0 || move > getCols(brd)){
		printw("Invalid move, try again.\n");
		refresh();
		return 0;
	}
	//make sure column not full
	if (getTop(brd,move)<0){
		printw("Column full, try again.\n");
		refresh();
		return 0;
	}
	return 1;
}

int main()
{
  clear();
  int chosen, cpu;
  int temp,numRows, numCols,status,xx,o;
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
	  	mvprintw(maxy / 4,maxx/6,"MUST BE AT LEAST 4x4, IF SMALLER WILL AUTOMATICALLY BECOME 4x4");
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
		clear();
		printBoard(mainBoard);


		for (;;)
		{

			int move;
			printw("Player %c where would you like to insert?\n",currPlayer);
			refresh();
			scanw("%i",&move);
			while(!valid(mainBoard,move)){
				scanw("%i",&move);
			}

			insertPiece(mainBoard,move,currPlayer);
			clear();
			printBoard(mainBoard);

			if(checkWin(mainBoard, currPlayer)){
				clear();
				printBoard(mainBoard);
				printw("Player %c has won!\nPress ENTER to Exit\n",currPlayer);
				writeWinner(currPlayer);
				refresh();
				getch();
				endwin();
				exit(0);
			}
			flipTurn();

		}

	    break;
 	case 1: /*1 player vs comp*/

		nodelay(stdscr, FALSE);
	  	clear();
	  	echo();
	  	curs_set(1);
	  	mvprintw(2, maxx / 4, "-----INPUT DESIRED BOARD SIZE-----");
	  	mvprintw(maxy / 4,maxx/6,"MUST BE AT LEAST 4x4, IF SMALLER WILL AUTOMATICALLY BECOME 4x4");
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

		BOARD *cBoard;
		cBoard = newBoard(numRows,numCols);
		clear();
		printBoard(cBoard);
		int move;


		for (;;)
		{
			printw("Player %c where would you like to insert?\n",currPlayer);
			refresh();
			scanw("%i",&move);
			while(!valid(cBoard,move)){
				scanw("%i",&move);
			}

			insertPiece(cBoard,move,currPlayer);
			printBoard(cBoard);
			if(checkWin(cBoard, currPlayer)){
				clear();
				printBoard(cBoard);
				printw("Player %c has won!\nPress ENTER to Exit",currPlayer);
				writeWinner(currPlayer);
				refresh();
				getch();
				endwin();
				exit(0);
			}
			if(boardFull(cBoard)){
				clear();
				printBoard(cBoard);
				printw("Cannot fit any more pieces in board. Result is draw\n");
				printw("Press ENTER to exit\n");
				refresh();
				getch();
				endwin();
				exit(0);
			}
			flipTurn();

			clear();
			cpu = bestMove(cBoard);
			insertPiece(cBoard,cpu,currPlayer);
			printBoard(cBoard);
			printw("CPU has moved to %i\n",cpu);
			refresh();

			if(checkWin(cBoard, currPlayer)){
				clear();
				printBoard(cBoard);
				printw("Player %c has won!\nPress ENTER to Exit",currPlayer);
				writeWinner(currPlayer);
				refresh();
				getch();
				endwin();
				exit(0);
			}
			if(boardFull(cBoard)){
				clear();
				printBoard(cBoard);
				printw("Cannot fit any more pieces in board. Result is draw\n");
				printw("Press ENTER to exit\n");
				refresh();
				getch();
				endwin();
				exit(0);
			}

			flipTurn();
		}

	    break;


	case 2: /* check scores*/

		nodelay(stdscr, FALSE);
		clear();
		if ((saveFile = fopen("scores.bin","r"))){
			fclose(saveFile);
		}
		else{
			eraseScores(saveFile);
		}
		saveFile = fopen("scores.bin","r+");
		fseek(saveFile,0,SEEK_SET);
		fscanf(saveFile,"%d",&xx);
		fscanf(saveFile,"%d",&o);
		mvprintw(maxy/4,maxx/6,"X WINS: %d",xx);
		mvprintw(maxy/4+2,maxx/6,"O WINS: %d",o);
		mvprintw(maxy/4+4,maxx/6,"PRESS ENTER TO RETURN");
	 	refresh();
	 	fclose(saveFile);
	 	getch();
	 	main();
	 	endwin();
	 	exit(0);
	    break;

	case 3: /* erase scores */
		eraseScores(saveFile);
		nodelay(stdscr, FALSE);
		refresh();
		getch();
		main();
		endwin();
		exit(0);
		break;
	case 4: /*quit*/
  	 	getch();
    	endwin();
 		exit(0);
    	break;

  default:
    break;
  }

//  endwin();
	return 1;
}
