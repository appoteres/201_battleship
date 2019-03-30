#ifndef __BG_INCLUDED__
#define __BG_INCLUDED__

#include <stdlib.h>
#include <stdio.h>

typedef struct board BOARD;

extern BOARD *newBoard(int row, int col);
extern void initializeBoard(BOARD *brd);
extern void printBoard(BOARD *brd);
extern void insertPiece(BOARD *brd,int position,char piece);
extern int checkWin(BOARD *brd, char piece);
extern int boardFull(BOARD *brd);

#endif