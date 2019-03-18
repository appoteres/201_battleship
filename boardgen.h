#ifndef __BG_INCLUDED__
#define __BG_INCLUDED__

#include <stdio.h>

typedef struct board Board;


extern Board *newBoard(int);
extern void printBoard(Board *this);
extern void insertPiece(Board *brd,int position,char piece);
extern int getNextSpot(Board *brd,int pos);

#endif