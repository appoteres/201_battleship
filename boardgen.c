#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "boardgen.h"

static char p1 = 'X';
static char p2 = 'O';



//board is always square
//board will take input from user for size parameter
//make that many sqaures
struct board
{
	int size;
	char index[1000][1000];
	//int numSquares;

} ;


Board *newBoard(int sqNum){
	Board *tempBoard = malloc(sizeof(Board));
	tempBoard->size = sqNum;
	for (int j = 0; j <sqNum; j++)
		for (int i = 0; i<sqNum; i++){
			//Square *temp = newSquare();
			tempBoard->index[j][i] = ' ';
		}
	return tempBoard;

}

void printBoard(Board *brd){
	//print positions above board
	int currentX = 0;
	int currentY = 0;
	
	for (int i =0;i<brd->size;i++){
		printf("  %i  ",i);
	}
	printf("\n");
				
	for(int q = 0;q<brd->size;q++){

		//print the top line
		for (int i =0;i<brd->size;i++){
			printf("#####");
		}
		printf("\n");

		//print the areas that hold the squares
		for (int j = 0;j<3;j++){
			for (int i =0;i<brd->size;i++){
				if (j == 1){
					printf("# %c #",brd->index[i][q]);
				}
				else{
					printf("#   #");
				}
			}
			printf("\n");
		}
	}
	
	//print the bottom line
	for (int i =0;i<brd->size;i++){
		printf("#####");
	}	
	printf("\n");
}
void insertPiece(Board *brd,int position,char piece){
	if (brd->index[position][brd->size-1] == ' '){
		printf("inserting\n");
		brd->index[position][brd->size-1] = piece;
		return;
	}
	else {
		for (int i = brd->size-1; i >= 0;i--){

		}
	}

}


#ifndef TESTINGBOARD
int main(int argc, char *argv[]){
	if (argc != 2){
		printf("please input size of board\n");
		return 1;
	}
	int size = atoi(argv[1]);
	Board *this = newBoard(size);
	printBoard(this);
	insertPiece(this,0,p1);
	insertPiece(this,0,p1);
	printBoard(this);



	// for (int i=0; i<size; i++){
	// 	for (int j =0; j<size; j++){
	// 		printf("[%i][%i] %c\n",i,j,this->index[i][j]);
	// 	}

	// }
}

#endif