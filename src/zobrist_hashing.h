//Pascal Schumann & Hendrik Junkawitsch

#ifndef CHESS_AI_ZOBRIST_HASHING_H
#define CHESS_AI_ZOBRIST_HASHING_H

#include <malloc.h>
#include "board.h"
#include "random_generator.h"

typedef struct zobrist_bitstrings
{
    int* data;
} ZobristBitstrings;

void zobrist_bitstrings_init(ZobristBitstrings *zobi);
void zobrist_bitstrings_generate(ZobristBitstrings *zobi);
void zobrist_bitstrings_destroy(ZobristBitstrings *zobi);
int zobrist_get_hash_key(Board *brd, ZobristBitstrings *zobi);

#endif //CHESS_AI_ZOBRIST_HASHING_H