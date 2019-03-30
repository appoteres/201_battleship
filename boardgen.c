#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "boardgen.h"

//board is always square
//board will take input from user for size parameter
//make that many sqaures
struct  board
{
	int NumRows;
	int NumCols;
	int **index;
	int *topTrack;
	int occupiedSquares;
};

// int checkFull(Board *brd,int col){
// 	//we know its full if the top row is full
// 	brd->index;
// }

BOARD *newBoard(int row, int col){
	//printf("board getting initialized\n");

	BOARD *tempBoard;
	tempBoard = malloc(sizeof(BOARD));
	
	if (tempBoard==0){
		printf("Allocating a BOARD: out of mem\n");
		exit(0);
	}

	tempBoard->NumCols = col;
	tempBoard->NumRows = row;


	tempBoard->index =  malloc(((tempBoard->NumRows-1) * sizeof(int*)));
	for(int i = 0;i <=tempBoard->NumRows-1;i++){
		tempBoard->index[i] = malloc(((tempBoard->NumCols-1) * sizeof(int)));
	}

	tempBoard->topTrack = malloc(tempBoard->NumCols * sizeof(int));


	//initialize all spots to 0, so we have a blank board
	initializeBoard(tempBoard);

	tempBoard->occupiedSquares =0;

	return tempBoard;

}

void initializeBoard(BOARD *brd){
	for (int i=0;i<brd->NumRows-1;i++){
		for(int j=0;j<brd->NumCols-1;j++){
			brd->index[i][j] = 0;
		}
	}
	for (int i=0;i<brd->NumCols;i++){
		brd->topTrack[i] = brd->NumRows-1;
	}
}

// 1 is X , 2 is O
void printBoard(BOARD *brd){
	//print positions above board
	for (int i =1;i<=brd->NumCols;i++){
		printf("%3i",i);
	}
	printf("\n");

	// for (int i=0;i<brd->NumCols;i++){
	// 	printf(" %i ",brd->topTrack[i]);
	// }
	// printf("\n");

	for (int i=0;i<brd->NumRows;i++){
		for(int j=0;j<brd->NumCols;j++){
			if(brd->index[i][j] == 1){
				printf("[X]");
			}
			else if(brd->index[i][j] == 2){
				printf("[O]");
			}
			else{
				printf("[ ]");
			}
		}
		printf("\n");
	}
	for (int i =0;i<brd->NumCols;i++){
		printf("---");
	}
	printf("\n");
}


void insertPiece(BOARD *brd,int column,char piece){
	//check valid move first
	//printf("attempt to insert in column %d\n",column);
	//printf("board dimensions are %d rows %d cols\n",brd->NumRows,brd->NumCols);

	while (column > brd->NumCols || column <= 0){
		printf("That is an invalid column, pick another\n");
		scanf("%i",&column);
	}
	while (brd->topTrack[column-1]<0){
		printf("That column is full, pick another\n");
		scanf("%i",&column);	
	}

	int input;
	//piece to num
	if (piece == 'X'){
		input = 1;
	}
	else {
		input = 2;
	}

	brd->index[brd->topTrack[column-1]][column-1] = input;
	brd->topTrack[column-1]--;
	//printf("inserted into row %i\n",brd->topTrack[column]-1);
	printBoard(brd);

	return;
}



int checkWin(BOARD *brd,char piece){
	int n;
	if (piece == 'X') n = 1;
	else if(piece == 'O') n = 2;
	
	//horizontal -- checking 
	for(int i=0;i<brd->NumRows;i++){
		for (int j = 0; j<brd->NumCols-3; j++)
		{
			//printf(" row %d col %d \n",i,j);
			if (	brd->index[i][j] == n 
				&&	brd->index[i][j+1] == n
				&&	brd->index[i][j+2] == n
				&&	brd->index[i][j+3] == n)
			{

				return 1;
			}		
		}
	}

	//vertical || checking
	for(int i=0;i<brd->NumCols;i++){
		for (int j = 3; j<brd->NumRows; j++)
		{
			if (	brd->index[j][i] == n 
				&&	brd->index[j-1][i] == n 
				&&	brd->index[j-2][i] == n
				&&	brd->index[j-3][i] == n)
			{
				return 1;
			}
		}
	}

	//diag // checking SW -> NE
	for (int i=0;i<brd->NumCols;i++){
		for(int j=brd->NumRows-1;j>2;j--){
			if(		brd->index[j][i] == n 
				&&	brd->index[j-1][i+1] == n
				&&	brd->index[j-2][i+2] == n
				&&	brd->index[j-3][i+3] == n)
			{
				return 1;
			}
		}
	}

	for (int i=brd->NumRows-1;i>2;i--){
		for(int j=brd->NumCols-1;j>2;j--){
			if(		brd->index[i][j] == n
				&&	brd->index[i-1][j-1] == n
				&&	brd->index[i-2][j-2] == n
				&&	brd->index[i-3][j-3] == n)
			{
				return 1;
			}
		}
	}

	//diag \\ checking SE -> NW

	return 0;
}


int boardFull(BOARD *brd){
	int sum = 0;
	for(int i=0;i < brd->NumCols;++i){
		sum +=brd->topTrack[i];
	}
	if (sum == (-1*brd->NumCols)) return 1;
	else return 0;
}