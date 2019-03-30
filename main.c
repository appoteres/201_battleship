#include <stdio.h>
#include <stdlib.h>
#include "boardgen.h"

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
	printf("Please input the dimensions of the board in 'NumberRows NumberCols' fashion.\nBe sure to include a space between dimensions\n");
	
	int numCols,numRows;

	scanf("%d %d",&numRows,&numCols);


	BOARD *mainBoard;
	mainBoard = newBoard(numRows,numCols);
	printBoard(mainBoard);
	

	for (;;)
	{
		

		int move;
		printf("Player %c Where would you like to insert?\n",currPlayer);
		scanf("%i",&move);
		
		insertPiece(mainBoard,move,currPlayer);
		flipTurn();
		


	}	
	return 0;
}