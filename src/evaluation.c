//Pascal Schumann & Hendrik Junkawitsch

#include "evaluation.h"

void evaluation_factor_tables_init(FactorTable* tables)
{
    double table_king[64] =     {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                                 -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                                 -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                                 -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                                 -2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0,
                                 -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0,
                                 2.0 , 2.0 , 0.0 , 0.0 , 0.0 , 0.0 , 2.0 , 2.0 ,
                                 2.0 , 3.0 , 1.0 , 0.0 , 0.0 , 1.0 , 3.0 , 2.0};

    double table_rook[64] =     {0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ,
                                 0.5 , 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5 ,
                                 -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
                                 -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
                                 -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
                                 -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
                                 -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5,
                                 0.0 , 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0};

    double table_bishop[64] =   {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
                                 -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0,
                                 -1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0,
                                 -1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0,
                                 -1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0,
                                 -1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0,
                                -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0};

    double table_queen[64] =    {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
                                 -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0,
                                 -1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0,
                                 -0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5,
                                 0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0,
                                 -1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0,
                                 -1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0,
                                 -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0};

    double table_pawn[64] =     {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0,
                                 1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0,
                                 0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5,
                                 0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0,
                                 0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5,
                                 0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5,
                                 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    double table_knigth[64] =   {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
                                 -4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0,
                                 -3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -4.0,
                                 -3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0,
                                 -3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0,
                                 -3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0,
                                 -4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0,
                                 -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0};

    tables[0].piece = WKING;
    tables[0].data = copy(table_king, 64);
    tables[1].piece = WQUEEN;
    tables[1].data = copy(table_queen, 64);
    tables[2].piece = WBISHOP;
    tables[2].data = copy(table_bishop, 64);
    tables[3].piece = WKNIGHT;
    tables[3].data = copy(table_knigth, 64);
    tables[4].piece = WROOK;
    tables[4].data = copy(table_rook, 64);
    tables[5].piece = WPAWN;
    tables[5].data = copy(table_pawn, 64);
    tables[6].piece = BKING;
    tables[6].data = rev_double_array(table_king, 64);
    tables[7].piece = BQUEEN;
    tables[7].data = rev_double_array(table_queen, 64);
    tables[8].piece = BBISHOP;
    tables[8].data = rev_double_array(table_bishop, 64);
    tables[9].piece = BKNIGHT;
    tables[9].data = rev_double_array(table_knigth, 64);
    tables[10].piece = BROOK;
    tables[10].data = rev_double_array(table_rook, 64);
    tables[11].piece = BPAWN;
    tables[11].data = rev_double_array(table_pawn, 64);
}

void evaluation_factor_tables_destroy(FactorTable* tables)
{
    for(int i = 0; i < 12; i++)
    {
        free(tables[i].data);
    }
}

double evaluate(Board *brd, FactorTable *tables)
{
    double factor = 10.0;
    double eval = 0;
    for(int address = 0; address < 64; address++)
    {
        switch(brd->data[address])
        {
            case WPAWN:
                eval += VALUE_PAWN + (get_table_by_piece(tables, WPAWN)).data[address]*factor;
                break;
            case WBISHOP:
                eval += VALUE_BISHOP + (get_table_by_piece(tables, WBISHOP)).data[address]*factor;
                break;
            case WKNIGHT:
                eval += VALUE_KNIGHT + (get_table_by_piece(tables, WKNIGHT)).data[address]*factor;
                break;
            case WROOK:
                eval += VALUE_ROOK + (get_table_by_piece(tables, WROOK)).data[address]*factor;
                break;
            case WKING:
                eval += VALUE_KING + (get_table_by_piece(tables, WKING)).data[address]*factor;
                break;
            case WQUEEN:
                eval += VALUE_QUEEN + (get_table_by_piece(tables, WQUEEN)).data[address]*factor;
                break;
            case BPAWN:
                eval -= VALUE_PAWN + (get_table_by_piece(tables, BPAWN)).data[address]*factor;
                break;
            case BBISHOP:
                eval -= VALUE_BISHOP + (get_table_by_piece(tables, BBISHOP)).data[address]*factor;
                break;
            case BKNIGHT:
                eval -= VALUE_KNIGHT + (get_table_by_piece(tables, BKNIGHT)).data[address]*factor;
                break;
            case BKING:
                eval -= VALUE_KING + (get_table_by_piece(tables, BKING)).data[address]*factor;
                break;
            case BQUEEN:
                eval -= VALUE_QUEEN + (get_table_by_piece(tables, BQUEEN)).data[address]*factor;
                break;
            case BROOK:
                eval -= VALUE_ROOK + (get_table_by_piece(tables, BROOK)).data[address]*factor;
                break;
        }
    }
    return eval;
}

FactorTable get_table_by_piece(FactorTable *tables, int piece)
{
    for(int i = 0; i < 12; i++)
    {
        if(tables[i].piece == piece) return tables[i];
    }
}