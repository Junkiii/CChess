//Pascal Schumann & Hendrik Junkawitsch

#ifndef CHESS_AI_PIECES_H
#define CHESS_AI_PIECES_H

#include "board.h"
#include "utilities.h"

#define BLACK   14
#define WHITE   13

#define WKING   1
#define WQUEEN  2
#define WROOK   3
#define WBISHOP 4
#define WKNIGHT 5
#define WPAWN   6

#define BKING   8
#define BQUEEN  9
#define BROOK   10
#define BBISHOP 11
#define BKNIGHT 12
#define BPAWN   13

#define MAXMOVES 139

int rook_potential_moves    (int position, int* moves);
int knight_potential_moves  (int position, int* moves);
int bishop_potential_moves  (int position, int* moves);
int king_potential_moves    (int position, int* moves);
int queen_potential_moves   (int position, int* moves);
int pawn_potential_moves    (int position, int* moves, int color_flag);

int rook_legal_move     (int position, int destination, Board *brd);
int knight_legal_move   (int position, int destination, Board *brd);
int bishop_legal_move   (int position, int destination, Board *brd);
int king_legal_move     (int position, int destination, Board *brd);
int queen_legal_move    (int position, int destination, Board *brd);
int pawn_legal_move     (int position, int destination, Board *brd);

#endif //CHESS_AI_PIECES_H