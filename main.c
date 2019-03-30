#include <stdlib.h>
#include <stdio.h>
#include "boardgen.h"
#include "engine.h"

static char currPlayer = 'X';

void flipTurn(){
	if (currPlayer== 'X'){
		currPlayer = 'O';
	}
	else currPlayer = 'X';
}


int main()
{
	// if (argc != 2){
	// 	printf("Please input size of board.\n");
	// 	return 1;
	// }
	printf("Please input the dimensions of the board in 'NumberRows NumberCols' fashion.\n");
	printf("Be sure to include a space between dimensions\n");
	printf("Any size smaller than 4x4 will be set to 4x4 automatically\n");
	
	int numCols,numRows;
	scanf("%d %d",&numRows,&numCols);

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
		
		int move;
		printf("Player %c Where would you like to insert?\n",currPlayer);
		scanf("%i",&move);
		
		if(boardFull(mainBoard)){
			printf("Cannot fit any more pieces in board.\n");
			exit(0);
		}
		insertPiece(mainBoard,move,currPlayer);
		if(checkWin(mainBoard, currPlayer)){
			printf("Player %c has won!\n",currPlayer);
			exit(0);
		}
		flipTurn();

	}	
	return 0;
}