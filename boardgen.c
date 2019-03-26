#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "boardgen.h"

static char p1 = 'X';
static char p2 = 'O';
static int flag = 0;
static char currPlayer = 'X';


//board is always square
//board will take input from user for size parameter
//make that many sqaures
struct board
{
	int size;
	char index[1000][1000];
	//int numSquares;

} ;

void flipTurn(){
	if (currPlayer== 'X'){
		currPlayer = 'O';
	}
	else currPlayer = 'X';
}

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
	
	for (int i =1;i<brd->size+1;i++){
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
	printf("Inserting...\n");
	brd->index[position][getNextSpot(brd,position)] = piece;
	printf("\nHere is the board after that move:\n");
	printBoard(brd);
	return;
}

int getNextSpot(Board *brd,int pos){
	int spot;
	if (brd->index[pos][brd->size-1] == ' '){
		spot = brd->size-1;
		return spot;
	}
	else{
		char temp;
		int size = brd->size-1;
		temp = brd->index[pos][brd->size-1];
		while(temp != ' '){
			temp = brd->index[pos][size--];
		}
		spot = size+1;
		return spot;
	}


}

void flip(){
	if (flag){
		flag = 0; 
	}
	else {
		flag = 1;
	}
}

#ifndef TESTINGBOARD
int main(int argc, char *argv[]){
	if (argc != 2){
		printf("Please input size of board.\n");
		return 1;
	}
	int size = atoi(argv[1]);
	Board *this = newBoard(size);
	printBoard(this);

	for (;;)
	{
		

		int move;
		printf("Player %c Where would you like to insert?\n",currPlayer);
		scanf("%i",&move);
		

		insertPiece(this,move-1,currPlayer);
		flipTurn();
		// if (flag == 0){
		// 	insertPiece(this,move-1,p1);
		// }
		// else{ 
		// 	insertPiece(this,move-1,p2);
		// }
		// flip(flag);
		


		// for (int i=0; i<size; i++){
		// 	for (int j =0; j<size; j++){
		// 		printf("[%i][%i] %c\n",i,j,this->index[i][j]);
		// 	}

		// }
	}	
}

#endif