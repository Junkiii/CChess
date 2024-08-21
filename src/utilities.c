//Pascal Schumann & Hendrik Junkawitsch

#include "utilities.h"

int max(int a, int b)
{
    return (a < b) ? b : a;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max_d(double a, double b)
{
    return (a > b) ? a : b;
}

int min_d(double a, double b)
{
    return (a < b) ? a : b;
}

int contains(int element, int* array, int length)
{
    for(int i = 0; i < length; i++)
    {
        if(array[i] == element) return 1;
    }
    return 0;
}

int swap_color(int color)
{
    return (color == WHITE) ? BLACK : WHITE;
}

double* rev_double_array(double* arr, int length)
{
    double* return_array = malloc(length * sizeof(double));
    int count = 0;
    for(int i = (length - 1); i > (-1); i--)
    {
        return_array[count] = arr[i];
        count++;
    }
    return return_array;
}

double * copy(double * arr, int length)
{
    double * result = malloc(sizeof(double) * length);
    for(int i = 0; i < length; i++)
    {
        result[i] = arr[i];
    }
    return result;
}

void copy_board(Board *brd, Board *copy) {
    board_init(copy);
    for(int i = 0; i < 64; i++)
    {
        copy->data[i] = brd->data[i];
    }
    copy->turn = brd->turn;
    copy->check = brd->check;
    copy->king_moved_white = brd->king_moved_white;
    copy->king_moved_black = brd->king_moved_black;
    copy->last_move_start = brd->last_move_start;
    copy->last_move_destination = brd->last_move_destination;
    copy->rook_left_moved_black = brd->rook_left_moved_black;
    copy->rook_right_moved_black = brd->rook_right_moved_black;
    copy->rook_left_moved_white = brd->rook_left_moved_white;
    copy->rook_right_moved_white = brd->rook_right_moved_white;
}




