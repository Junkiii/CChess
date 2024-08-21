//Pascal Schumann & Hendrik Junkawitsch

#include "cchess.h"
#include "forsyth_edwards_notation.h"

void cchess_start_game_against_ai(int opponent_color, int difficulty)
{
    //Setting up the board
    Board brd;
    board_init(&brd);
    board_starting_position(&brd);

    //Generating factor tables for evaluation
    FactorTable tables[12];
    evaluation_factor_tables_init(tables);

    //Set up start_index
    int start_index;
    (opponent_color == WHITE) ? (start_index = 0) : (start_index = 1);

    //Print out board with starting position:
    board_print(&brd);

    //Run the game loop
    for(int i = start_index; i < 200; i++)      //Change this for-loop
    {
        if(i % 2 == 0)
        {
            int turn = brd.turn;
            while(brd.turn == turn)
            {
                char position_str[3], destination_str[3];
                scanf("%s", position_str);
                scanf("%s", destination_str);
                int position = board_get_address_from_square(position_str);
                int destination = board_get_address_from_square(destination_str);
                board_make_move(position, destination, &brd);
                if(brd.turn != turn)
                {
                    printf("\n\n");
                    board_print(&brd);
                }
                else
                {
                    printf("ChessLegalError: Move not possible\n");
                }
            }
        }
        else
        {
            call_minimax(&brd, tables, difficulty);
            printf("\n\n");
            board_print(&brd);
        }
    }

    evaluation_factor_tables_destroy(tables);
    board_destroy(&brd);
}
