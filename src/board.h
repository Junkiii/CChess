//Pascal Schumann & Hendrik Junkawitsch

#ifndef CHESS_AI_BOARD_H
#define CHESS_AI_BOARD_H

typedef struct board
{
    int* data;
    int check;
    int king_moved_black, king_moved_white;
    int turn;
    int rook_left_moved_white, rook_right_moved_white, rook_left_moved_black, rook_right_moved_black;
    int last_move_start, last_move_destination;

} Board;

#include <stdlib.h>
#include "pieces.h"

void board_init(Board* brd);
void board_starting_position(Board* brd);
void board_destroy(Board* brd);
void board_get_2d_coords(int *x, int *y, int position);
int board_get_address(int x, int y);
int board_out_of_bounds(int position);
int board_on_pawn_row(int position, int color_flag);
int board_get_piece_color(int position, Board*  brd);
void board_get_distance(int start, int destination, int *x, int *y);
int board_get_piece_from_coords(Board  *brd, int x, int y);
void board_force_move(int start, int destination, Board *brd);
void board_print(Board  *brd);
int board_piece_in_attack(int square, Board  *brd);
int board_check_move(int start, int destination, Board  *brd, int turn);
int board_get_address_from_square(char* square);
void board_make_move(int position, int destination, Board *brd);
int board_get_possible_moves(Board *brd, Board *moves);

#endif //CHESS_AI_BOARD_H