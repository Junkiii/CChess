//Pascal Schumann & Hendrik Junkawitsch

#ifndef CHESS_AI_MINIMAX_H
#define CHESS_AI_MINIMAX_H

#include "board.h"
#include "evaluation.h"


void call_minimax(Board *brd, FactorTable *tables, int depth);
double minimax(Board *brd, FactorTable *tables, int depth, double alpha, double beta);
void destroy_moves(Board *moves, int move_count);

#endif //CHESS_AI_MINIMAX_H
