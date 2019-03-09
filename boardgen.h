#ifndef __BG_INCLUDED__
#define __BG_INCLUDED__

#include <stdio.h>

typedef struct board Board;

extern Board *newBoard(int);
extern void printBoard(Board *this);

#endif