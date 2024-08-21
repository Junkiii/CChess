//Pascal Schumann & Hendrik Junkawitsch

#ifndef CHESS_AI_UTILITIES_H
#define CHESS_AI_UTILITIES_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"

int max(int a, int b);
int min(int a, int b);
int max_d(double a, double b);
int min_d(double a, double b);
int contains(int element, int* array, int length);
int swap_color(int color);
double* rev_double_array(double* arr, int length);
double * copy(double * arr, int length);
void copy_board(Board *brd, Board *copy);


#endif //CHESS_AI_UTILITIES_H