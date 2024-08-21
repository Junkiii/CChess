//Pascal Schumann & Hendrik Junkawitsch

#ifndef CHESS_AI_EVALUATION_H
#define CHESS_AI_EVALUATION_H

#define VALUE_PAWN      100
#define VALUE_ROOK      500
#define VALUE_KNIGHT    350
#define VALUE_BISHOP    350
#define VALUE_QUEEN     900
#define VALUE_KING      20000

#include "pieces.h"

typedef struct factor_table
{
    int piece;
    double *data;
} FactorTable;

void evaluation_factor_tables_init(FactorTable* tables);
void evaluation_factor_tables_destroy(FactorTable* tables);
double evaluate(Board *brd, FactorTable *tables);
FactorTable get_table_by_piece(FactorTable *tables, int piece);

#endif //CHESS_AI_EVALUATION_H
