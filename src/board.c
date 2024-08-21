//Pascal Schumann & Hendrik Junkawitsch

#include "board.h"

void board_init(Board* brd)
{
    brd->data = malloc(64*sizeof(int));
}

void board_clear(Board* brd)
{
    if(brd->data == NULL) return;
    for(int i = 0; i < 64; i++) brd->data[i] = 0;
}

void board_starting_position(Board* brd)
{
    if(brd->data == NULL)
    {
        return;
    }
    board_clear(brd);
    //place white pieces
    for(int i = 48; i < 56; i++)
    {
        brd->data[i] = WPAWN;
    }
    brd->data[56] = WROOK;
    brd->data[57] = WKNIGHT;
    brd->data[58] = WBISHOP;
    brd->data[59] = WQUEEN;
    brd->data[60] = WKING;
    brd->data[61] = WBISHOP;
    brd->data[62] = WKNIGHT;
    brd->data[63] = WROOK;

    //place black pieces
    for(int i = 8; i < 16; i++)
    {
        brd->data[i] = BPAWN;
    }
    brd->data[0] = BROOK;
    brd->data[1] = BKNIGHT;
    brd->data[2] = BBISHOP;
    brd->data[3] = BQUEEN;
    brd->data[4] = BKING;
    brd->data[5] = BBISHOP;
    brd->data[6] = BKNIGHT;
    brd->data[7] = BROOK;

    brd->turn = WHITE;
    brd->check = -1;
    brd->king_moved_black = 0;
    brd->king_moved_white = 0;
    brd->rook_left_moved_black = 0;
    brd->rook_left_moved_white = 0;
    brd->rook_right_moved_black = 0;
    brd->rook_right_moved_white = 0;
    brd->last_move_destination = -1;
    brd->last_move_start = -1;
}

void board_destroy(Board* brd)
{
    free(brd->data);
}

void board_get_2d_coords(int *x, int *y, int position)
{
    *x = position % 8;
    *y = position / 8;
}

int board_get_address(int x, int y)
{
    return (y * 8 + x);
}

int board_out_of_bounds(int position)
{
    return ((position < 0) || (position > 63)) ? 1 : 0;
}

int board_on_pawn_row(int position, int color_flag)
{
    if((color_flag == WHITE) && (position > 47) && (position < 56)) return 1;
    else if((color_flag == BLACK) && (position > 7) && (position < 16)) return 1;
    return 0;
}

int board_get_piece_color(int position, Board*  brd)
{
    if((brd->data[position] > 0) && (brd->data[position] < 7)) return WHITE;
    else if((brd->data[position] == 0)) return -1;
    else return BLACK;
}

void board_get_distance(int start, int destination, int *x, int *y)
{
    int x_tmp_1, y_tmp_1;
    int x_tmp_2, y_tmp_2;
    board_get_2d_coords(&x_tmp_1, &y_tmp_1, start);
    board_get_2d_coords(&x_tmp_2, &y_tmp_2, destination);
    *x = abs(x_tmp_1 - x_tmp_2);
    *y = abs(y_tmp_1 - y_tmp_2);
}

int board_get_piece_from_coords(Board  *brd, int x, int y){
    return brd->data[board_get_address(x, y)];
}

void board_print(Board  *brd){
    for(int i = 0; i < 8; i++){
        printf("-----------------------------------------\n");
        printf("|");
        for(int j = 0; j < 8; j++){
            int temp = board_get_piece_from_coords(brd, j, i);
            switch(temp){
                case WROOK:
                    printf(" WR |");
                    break;
                case WKNIGHT:
                    printf(" WN |");
                    break;
                case WBISHOP:
                    printf(" WB |");
                    break;
                case WQUEEN:
                    printf(" WQ |");
                    break;
                case WKING:
                    printf(" WK |");
                    break;
                case WPAWN:
                    printf(" WP |");
                    break;
                case BROOK:
                    printf(" BR |");
                    break;
                case BKNIGHT:
                    printf(" BN |");
                    break;
                case BBISHOP:
                    printf(" BB |");
                    break;
                case BQUEEN:
                    printf(" BQ |");
                    break;
                case BKING:
                    printf(" BK |");
                    break;
                case BPAWN:
                    printf(" BP |");
                    break;
                default:
                    printf("    |");
            }
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
}

void board_force_move(int start, int destination, Board *brd)
{
    int piece = brd->data[start];
    brd->data[start] = 0;
    brd->data[destination] = piece;
}

int board_piece_in_attack(int square, Board *brd)
{
    if(brd->data[square] == 0) return 0;
    int return_val = 0;
    for(int i = 0; i < 64; i++)
    {
        if(i != square)
        {
            return_val = return_val | board_check_move(i, square, brd, brd->turn);
        }
    }
    return return_val;
}

int board_check_move(int start, int destination, Board *brd, int turn)
{
    int piece = brd->data[start];
    int count = 0;
    int pot_moves[27];

    switch(piece)
    {
        case WPAWN:
            count = pawn_potential_moves(start, pot_moves, WHITE);
            if((contains(destination, pot_moves, count)) && (turn == WHITE))
            {
                return pawn_legal_move(start, destination, brd);
            }
            break;
        case WBISHOP:
            count = bishop_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == WHITE))
            {
                return bishop_legal_move(start, destination, brd);
            }
            break;
        case WKNIGHT:
            count = knight_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == WHITE))
            {
                return knight_legal_move(start, destination, brd);
            }
            break;
        case WROOK:
            count = rook_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == WHITE))
            {
                return rook_legal_move(start, destination, brd);
            }
            break;
        case WKING:
            count = king_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == WHITE))
            {
                return king_legal_move(start, destination, brd);
            }
            break;
        case WQUEEN:
            count = queen_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == WHITE))
            {
                return queen_legal_move(start, destination, brd);
            }
            break;
        case BPAWN:
            count = pawn_potential_moves(start, pot_moves, BLACK);
            if((contains(destination, pot_moves, count)) && (turn == BLACK))
            {
                return pawn_legal_move(start, destination, brd);
            }
            break;
        case BBISHOP:
            count = bishop_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == BLACK))
            {
                return bishop_legal_move(start, destination, brd);
            }
            break;
        case BKNIGHT:
            count = knight_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == BLACK))
            {
                return knight_legal_move(start, destination, brd);
            }
            break;
        case BKING:
            count = king_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == BLACK))
            {
                return king_legal_move(start, destination, brd);
            }
            break;
        case BQUEEN:
            count = queen_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == BLACK))
            {
                return queen_legal_move(start, destination, brd);
            }
            break;
        case BROOK:
            count = rook_potential_moves(start, pot_moves);
            if((contains(destination, pot_moves, count)) && (turn == BLACK))
            {
                return rook_legal_move(start, destination, brd);
            }
            break;
        default:
            return 0;
    }
    return 0;
}

int board_get_address_from_square(char* square)
{
    int letter;
    if((int)square[0] < 91) letter = (int)square[0] - 65;
    else letter = (int)square[0] - 97;
    int number = (int)square[1] - 49;
    switch(number)
    {
        case 0: number = 7; break;
        case 1: number = 6; break;
        case 2 : number = 5; break;
        case 3 : number = 4; break;
        case 4 : number = 3; break;
        case 5 : number = 2; break;
        case 6 : number = 1; break;
        case 7 : number = 0; break;
    }
    return board_get_address(letter, number);
}

void board_make_move(int position, int destination, Board *brd)
{
    if(board_check_move(position, destination, brd, brd->turn))
    {
        //Check if the move is a pawn move
        if((brd->data[position] == WPAWN) || (brd->data[position] == BPAWN)) {
            brd->last_move_start = position;
            brd->last_move_destination = destination;
            //Check for an en passant move
            int x, y;
            int x_dest, y_dest;
            board_get_2d_coords(&x, &y, position);
            board_get_2d_coords(&x_dest, &y_dest, destination);
            if ((abs(x - x_dest) > 0) && (brd->data[destination] == 0)) {
                if (x < x_dest) {
                    brd->data[position + 1] = 0;        //Capture right pawn
                } else {
                    brd->data[position - 1] = 0;        //Capture left pawn
                }
            }
            board_force_move(position, destination, brd);
        }
        else if((brd->data[position] == WKING) || (brd->data[position] == BKING))           //castle
        {
            int x, y;
            int x_dest, y_dest;
            board_get_2d_coords(&x, &y, position);
            board_get_2d_coords(&x_dest, &y_dest, destination);

            if((x - x_dest) == -2)          //short castle (right)
            {
                board_force_move(position, destination, brd);
                board_force_move(position+3, position+1, brd);
            }
            else if((x - x_dest) == 2)      //long castle (left)
            {
                board_force_move(position, destination, brd);
                board_force_move(position-4, position-1, brd);
            }
            else
            {
                board_force_move(position, destination, brd);
            }

            brd->last_move_start = -1;
            brd->last_move_destination = -1;
        }
        else
        {
            brd->last_move_start = -1;
            brd->last_move_destination = -1;
            board_force_move(position, destination, brd);
        }
        brd->turn = swap_color(brd->turn);
    }
}

int board_get_possible_moves(Board *brd, Board *moves)
{
    int move_count = 0;

    for(int i = 0; i < 64; i++)
    {
        if(brd->data[i] == 0) continue;

        int piece = brd->data[i];
        int count = 0;
        int pot_moves[27];

        if(brd->turn == WHITE)
        {
            switch(piece)
            {
                case WPAWN:
                    count = pawn_potential_moves(i, pot_moves, WHITE);
                    for (int j = 0; j < count; j++) {
                        if (pawn_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case WBISHOP:
                    count = bishop_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (bishop_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case WKNIGHT:
                    count = knight_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (knight_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case WROOK:
                    count = rook_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (rook_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case WKING:
                    count = king_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (king_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case WQUEEN:
                    count = queen_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (queen_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                default:

                    break;
            }
        }
        else if(brd->turn == BLACK)
        {
            switch(piece)
            {
                case BPAWN:
                    count = pawn_potential_moves(i, pot_moves, BLACK);
                    for (int j = 0; j < count; j++) {
                        if (pawn_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case BBISHOP:
                    count = bishop_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (bishop_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case BKNIGHT:
                    count = knight_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (knight_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case BKING:
                    count = king_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (king_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case BQUEEN:
                    count = queen_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (queen_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                case BROOK:
                    count = rook_potential_moves(i, pot_moves);
                    for (int j = 0; j < count; j++) {
                        if (rook_legal_move(i, pot_moves[j], brd)) {
                            copy_board(brd, &moves[move_count]);
                            board_make_move(i, pot_moves[j], &moves[move_count]);
                            move_count++;
                        }
                    }
                    break;
                default:

                    break;
                }
            }
        }

    return move_count;
}


