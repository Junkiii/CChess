//Pascal Schumann & Hendrik Junkawitsch

#include "forsyth_edwards_notation.h"

void fen_get_board(Board* brd, char* notation)
{
    int count = 0;
    int field_address = 0;

    while(notation[count] != 32)
    {
        switch(notation[count])
        {
            case 114:
                brd->data[field_address] = BROOK;
                field_address++;
                break;
            case 110:
                brd->data[field_address] = BKNIGHT;
                field_address++;
                break;
            case 98:
                brd->data[field_address] = BBISHOP;
                field_address++;
                break;
            case 113:
                brd->data[field_address] = BQUEEN;
                field_address++;
                break;
            case 107:
                brd->data[field_address] = BKING;
                field_address++;
                break;
            case 112:
                brd->data[field_address] = BPAWN;
                field_address++;
                break;
            case 82:
                brd->data[field_address] = WROOK;
                field_address++;
                break;
            case 78:
                brd->data[field_address] = WKNIGHT;
                field_address++;
                break;
            case 66:
                brd->data[field_address] = WBISHOP;
                field_address++;
                break;
            case 81:
                brd->data[field_address] = WQUEEN;
                field_address++;
                break;
            case 75:
                brd->data[field_address] = WKING;
                field_address++;
                break;
            case 80:
                brd->data[field_address] = WPAWN;
                field_address++;
                break;
            case 47:
                //new row
                break;
            default:
                if((notation[count] > 48) && (notation[count] < 57))
                {
                    int empty_squares = notation[count] - 48;
                    for(int i = 0; i < empty_squares; i++)
                    {
                        field_address++;
                    }
                }
                break;
        }
        count++;
    }

    count++;

    if(notation[count] == 119) brd->turn = WHITE;
    else if(notation[count] == 98) brd->turn = BLACK;

    count++;
    count++;

    brd->king_moved_black = 1;
    brd->king_moved_white = 1;
    brd->rook_left_moved_white = 1;
    brd->rook_right_moved_white = 1;
    brd->rook_left_moved_black = 1;
    brd->rook_right_moved_black = 1;

    while(notation[count] != 32)
    {
        switch(notation[count])
        {
            case 75:
                brd->king_moved_white = 0;
                brd->rook_right_moved_white = 0;
                count++;
                break;
            case 81:
                brd->king_moved_white = 0;
                brd->rook_left_moved_white = 0;
                count++;
                break;
            case 107:
                brd->king_moved_black = 0;
                brd->rook_right_moved_black = 0;
                count++;
                break;
            case 113:
                brd->king_moved_black = 0;
                brd->rook_left_moved_black = 0;
                count++;
                break;
            case 45:
                //no castle is possible
                count++;
                break;
        }
    }

    count++;

    if(notation[count] == 45)
    {
        brd->last_move_destination = -1;
        brd->last_move_start = -1;
        count++;
    }
    else
    {
        char letter = notation[count];
        count++;
        int number = notation[count] - 49;
        count++;

        int x = letter - 97;
        int y;
        switch(number)
        {
            case 0:
                y = 7;
                break;
            case 1:
                y = 6;
                break;
            case 2:
                y = 5;
                break;
            case 3:
                y = 4;
                break;
            case 4:
                y = 3;
                break;
            case 5:
                y = 2;
                break;
            case 6:
                y = 1;
                break;
            case 7:
                y = 1;
                break;
        }
        int address = board_get_address(x, y);
        if(address > 31)
        {
            brd->last_move_start = address - 8;
            brd->last_move_destination = address + 8;
        }
        else
        {
            brd->last_move_start = address + 8;
            brd->last_move_destination = address - 8;
        }
    }
}