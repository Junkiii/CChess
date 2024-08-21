//Pascal Schumann & Hendrik Junkawitsch

#include "minimax.h"

void call_minimax(Board *brd, FactorTable *tables, int depth)
{
    Board *moves;

    //Array of boards for every move:
    moves = malloc(MAXMOVES * sizeof(Board));

    int move_count = board_get_possible_moves(brd, moves);

    if(move_count > 0)
    {
        double minimax_eval = minimax(&moves[0], tables, depth-1, -INFINITY, INFINITY);
        int best_move_index = 0;

        for (int i = 1; i < move_count; i++)
        {
            double eval = minimax(&moves[i], tables, depth-1, -INFINITY, INFINITY);
            switch(brd->turn)
            {
                case WHITE:
                    if(eval > minimax_eval)
                    {
                        minimax_eval = eval;
                        best_move_index = i;
                    }
                    break;
                case BLACK:

                    if(eval < minimax_eval)
                    {
                        minimax_eval = eval;
                        best_move_index = i;
                    }
                    break;
            }
        }

        copy_board(&moves[best_move_index], brd);
        destroy_moves(moves, move_count);
    }
    else
    {
        printf("Fatal Error occurred: No move found in function 'call_minimax'");
        destroy_moves(moves, move_count);
        abort();
    }
}

double minimax(Board *brd, FactorTable *tables, int depth, double alpha, double beta)
    {
    if(depth == 0)
    {
        return (evaluate(brd, tables));
    }
    else
    {
        Board *moves;
        moves = malloc(MAXMOVES * sizeof(Board));
        int move_count = board_get_possible_moves(brd, moves);

        if(move_count > 0)
        {
            double minimax_eval = minimax(&moves[0], tables, depth-1, alpha, beta);

            for(int i = 0; i < move_count; i++)
            {
                double eval = minimax(&moves[i], tables, depth-1, alpha, beta);
                switch(brd->turn)
                {
                    case WHITE:
                        if(eval > minimax_eval)
                        {
                            minimax_eval = eval;
                            alpha = max_d(alpha, eval);
                            if(beta <= alpha) break;
                        }
                        break;
                    case BLACK:
                        if(eval < minimax_eval)
                        {
                            minimax_eval = eval;
                            beta = min_d(beta, eval);
                            if(beta <= alpha) break;
                        }
                        break;
                }
            }
            destroy_moves(moves, move_count);
            return minimax_eval;
        }
        else
        {
            printf("Fatal Error occurred: No move found in function 'minimax'");
            destroy_moves(moves, move_count);
            abort();
        }
    }
}

void destroy_moves(Board *moves, int move_count)
{
    for(int i = 0; i < move_count; i++)
    {
        board_destroy(&moves[i]);
    }
    free(moves);
}
