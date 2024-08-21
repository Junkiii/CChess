//Pascal Schumann & Hendrik Junkawitsch

#include "pieces.h"

int rook_potential_moves(int position, int moves[])
{
    int move_counter = 0;
    int x, y;
    board_get_2d_coords(&x, &y, position);

    //get potential horizontal moves
    for(int i = position-x; i < (position-x)+8; i++)
    {
        if(i != position)
        {
            moves[move_counter] = i;
            move_counter++;
        }
    }

    //get potential vertical moves
    for(int i = position-y*8; i <= (position-y*8)+56; i += 8)
    {
        if(i != position)
        {
            moves[move_counter] = i;
            move_counter++;
        }
    }
    return move_counter;
}

int knight_potential_moves(int position, int* moves)
{
    int move_counter = 0;
    int x,y;
    board_get_2d_coords(&x, &y, position);

    //Check if the knight stands on the edges of the board
    int a = -2;
    int b = 3;
    if(x == 0) a = 0;
    else if(x == 1) a = -1;
    else if(x == 6) b = 2;
    else if(x == 7) b = 1;

    //get the potential moves
    for(int i = a; i < b; i++)
    {
        if(i != 0)
        {
            int move_1 = (position + i) + 8*(((i + 2) % 2)+1);
            int move_2 = (position + i) - 8*(((i + 2) % 2)+1);
            if(!board_out_of_bounds(move_1))
            {
                moves[move_counter] = move_1;
                move_counter++;
            }
            if(!board_out_of_bounds(move_2))
            {
                moves[move_counter] = move_2;
                move_counter++;
            }
        }
    }
    return move_counter;
}

int bishop_potential_moves(int position, int* moves)
{
    int move_counter = 0;
    int x,y;
    board_get_2d_coords(&x, &y, position);

    //get potential diagonal moves
    int x_counter = x;
    for(int i = position-x; i < (position-x)+8; i++)
    {
        if(i != position)
        {
            int move_1 = i - (8*x_counter);
            int move_2 = i + (8*x_counter);
            if(!board_out_of_bounds(move_1))
            {
                moves[move_counter] = move_1;
                move_counter++;
            }
            if(!board_out_of_bounds(move_2))
            {
                moves[move_counter] = move_2;
                move_counter++;
            }
        }
        x_counter--;
    }
    return move_counter;
}

int king_potential_moves(int position, int* moves)
{
    int move_counter = 0;
    int x,y;
    board_get_2d_coords(&x, &y, position);

    //Check if the knight stands on the edges of the board
    int a = -1;
    int b = 2;
    if(x == 0) a = 0;
    else if(x == 7) b = 1;

    //get all potential move for the king
    for(int i = a; i < b; i++)
    {
        int move_1 = (position + i)+8;
        if(!board_out_of_bounds(move_1))
        {
            moves[move_counter] = move_1;
            move_counter++;
        }
        int move_2 = (position + i)-8;
        if(!board_out_of_bounds(move_2))
        {
            moves[move_counter] = move_2;
            move_counter++;
        }
        if(i != 0)
        {
            int move_3 = (position + i);
            if(!board_out_of_bounds(move_3))
            {
                moves[move_counter] = move_3;
                move_counter++;
            }
        }
    }

    if(position == 60)
    {
        moves[move_counter] = 58;
        move_counter++;
        moves[move_counter] = 62;
        move_counter++;
    }
    else if(position == 4)
    {
        moves[move_counter] = 6;
        move_counter++;
        moves[move_counter] = 2;
        move_counter++;
    }

    return move_counter;
}

int queen_potential_moves(int position, int* moves)
{
    int moves_diagonal[13];
    int moves_straight[14];
    //get the moves from the rook function and the bishop function
    int count_diagonal = bishop_potential_moves(position, moves_diagonal);
    int count_straight = rook_potential_moves(position, moves_straight);

    //write the moves into the final moves array
    for(int i = 0; i < count_diagonal; i++)
    {
        moves[i] = moves_diagonal[i];
    }
    for(int i = count_diagonal; i < (count_diagonal+count_straight); i++)
    {
        moves[i] = moves_straight[i-count_diagonal];
    }
    return (count_diagonal + count_straight);
}

int pawn_potential_moves(int position, int* moves, int color_flag)
{
    int move_counter = 0;
    int x,y;
    board_get_2d_coords(&x, &y, position);
    int double_step = board_on_pawn_row(position, color_flag);

    int double_step_increment = -16;
    int step_increment = -8;
    if(color_flag == BLACK)
    {
        double_step_increment *= -1;
        step_increment *= -1;
    }

    int a = -1;
    int b = 2;
    if(x == 0) a = 0;
    else if(x == 7) b = 1;
    for(int i = a; i < b; i++)
    {
        int move = position + i + step_increment;
        if(!board_out_of_bounds(move))
        {
            moves[move_counter] = move;
            move_counter++;
        }
    }
    if(double_step)
    {
        int move = position + double_step_increment;
        if(!board_out_of_bounds(move))
        {
            moves[move_counter] = move;
            move_counter++;
        }
    }
    return move_counter;
}

int rook_legal_move(int position, int destination, Board *brd)
{
    int x,y;
    int dest_x, dest_y;
    board_get_2d_coords(&x, &y, position);
    board_get_2d_coords(&dest_x, &dest_y, destination);

    int increment = 1;
    if(dest_y < y) increment = -8;
    else if(dest_y > y) increment = 8;
    else if(dest_x < x) increment = -1;

    int distance_x, distance_y;
    board_get_distance(position, destination, &distance_x, &distance_y);
    int distance = max(distance_x, distance_y);

    for(int i = 0; i < distance; i++)
    {
        position += increment;
        if(position != destination)
        {
            if(board_get_piece_color(position, brd) != -1) return 0;
        }
        else {
            if(board_get_piece_color(position, brd) == brd->turn) return 0;
        }
    }
    return 1;
}

int knight_legal_move(int position, int destination, Board *brd)
{
    if(board_get_piece_color(destination, brd) == brd->turn) return 0;
    return 1;
}

int bishop_legal_move(int position, int destination, Board *brd) {
    int x, y;
    int dest_x, dest_y;
    board_get_2d_coords(&x, &y, position);
    board_get_2d_coords(&dest_x, &dest_y, destination);

    int increment_x = 1;
    int increment_y = 8;
    if ((x < dest_x) && (y > dest_y)) increment_y = -8;
    else if ((x > dest_x) && (y > dest_y))
    {
        increment_x = -1;
        increment_y = -8;

    }
    else if ((x > dest_x) && (y < dest_y)) increment_x = -1;

    int distance;
    board_get_distance(position, destination, &distance, &distance);

    for(int i = 0; i < distance; i++)
    {
        position = position + increment_x + increment_y;
        if(position != destination)
        {
            if(board_get_piece_color(position, brd) != -1) return 0;
        }
        else {
            if(board_get_piece_color(position, brd) == brd->turn) return 0;
        }
    }
    return 1;
}

int king_legal_move(int position, int destination, Board *brd)
{
    int x,y, dest_x, dest_y;
    board_get_2d_coords(&x, &y, position);
    board_get_2d_coords(&dest_x, &dest_y, destination);
    int distance_x = abs(dest_x - x);
    int castle = 0;
    if(distance_x == 2) castle = 1;

    if(!castle)
    {
        if(board_get_piece_color(destination, brd) == brd->turn) return 0;
    }
    else
    {
        if(brd->turn == WHITE)
        {
            if(destination == 62)
            {
                if((brd->king_moved_white != 0) || (brd->rook_right_moved_white != 0)) return 0;
                if((board_get_piece_color(61, brd) != -1) || (board_get_piece_color(62, brd) != -1)) return 0;
                brd->turn = BLACK;
                board_force_move(60, 61, brd);
                if(board_piece_in_attack(61, brd))
                {
                    board_force_move(61, 60, brd);
                    brd->turn = WHITE;
                    return 0;
                }
                else
                {
                    board_force_move(61, 60, brd);
                    brd->turn = WHITE;
                }
            }
            else if(destination == 58)
            {
                if((brd->king_moved_white != 0) || (brd->rook_left_moved_white != 0)) return 0;
                if((board_get_piece_color(59, brd) != -1) || (board_get_piece_color(58, brd) != -1)) return 0;
                brd->turn = BLACK;
                board_force_move(60, 59, brd);
                if(board_piece_in_attack(59, brd))
                {
                    board_force_move(59, 60, brd);
                    brd->turn = WHITE;
                    return 0;
                }
                else
                {
                    board_force_move(59, 60, brd);
                    brd->turn = WHITE;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(destination == 6)
            {
                if((brd->king_moved_black != 0) || (brd->rook_right_moved_black != 0)) return 0;
                if((board_get_piece_color(6, brd) != -1) || (board_get_piece_color(5, brd) != -1)) return 0;
                brd->turn = WHITE;
                board_force_move(4, 5, brd);
                if(board_piece_in_attack(5, brd))
                {
                    board_force_move(5, 4, brd);
                    brd->turn = BLACK;
                    return 0;
                }
                else
                {
                    board_force_move(5, 4, brd);
                    brd->turn = BLACK;
                }

            }
            else if(destination == 2)
            {
                if((brd->king_moved_black != 0) || (brd->rook_left_moved_black != 0)) return 0;
                if((board_get_piece_color(2, brd) != -1) || (board_get_piece_color(3, brd) != -1)) return 0;
                brd->turn = WHITE;
                board_force_move(4, 3, brd);
                if(board_piece_in_attack(3, brd))
                {
                    board_force_move(3, 4, brd);
                    brd->turn = BLACK;
                    return 0;
                }
                else
                {
                    board_force_move(3, 4, brd);
                    brd->turn = BLACK;
                }
            }
            else
            {
                return 0;
            }
        }
    }

    return 1;
}

int queen_legal_move(int position, int destination, Board *brd)
{
    int x, y;
    int dest_x, dest_y;
    board_get_2d_coords(&x, &y, position);
    board_get_2d_coords(&dest_x, &dest_y, destination);

    int distance_x, distance_y;
    board_get_distance(position, destination, &distance_x, &distance_y);

    if(distance_x == distance_y)
    {
        return bishop_legal_move(position, destination, brd);
    }
    else
    {
        return rook_legal_move(position, destination, brd);
    }
}

int pawn_legal_move(int position, int destination, Board *brd)
{
    int pos = position;
    int x,y;
    int dest_x, dest_y;
    board_get_2d_coords(&x, &y, position);
    board_get_2d_coords(&dest_x, &dest_y, destination);

    //Fixing straight capturing:

    int increment_x, increment_y;
    increment_x = 0;
    if(dest_x < x) increment_x = -1;
    else if(dest_x > x) increment_x = 1;

    int distance_x, distance_y;
    board_get_distance(position, destination, &distance_x, &distance_y);
    int distance = max(distance_x, distance_y);

    if(brd->turn == WHITE)
    {
        increment_y = -8;
    }
    else
    {
        increment_y = 8;
    }

    for(int i = 0; i < distance; i++)
    {
        position = position + increment_x + increment_y;

        if(increment_x != 0)
        {
            if(board_get_piece_color(position, brd) == brd->turn) return 0;
            if(board_get_piece_color(position, brd) == -1)
            {
                if(brd->last_move_start == -1) return 0;
                if((brd->last_move_start != (pos + increment_x + 2*increment_y)) || (brd->last_move_destination != (pos + increment_x))) return 0;
            }
        }
        else
        {
            if(position != destination)
            {
                if(board_get_piece_color(position, brd) != -1) return 0;
            }
            else {
                if(board_get_piece_color(position, brd) == brd->turn) return 0;
                if(board_get_piece_color(position, brd) == swap_color(brd->turn)) return 0;
            }
        }
    }
    return 1;
}

