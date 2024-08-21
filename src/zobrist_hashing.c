//Pascal Schumann & Hendrik Junkawitsch

#include "zobrist_hashing.h"

void zobrist_bitstrings_init(ZobristBitstrings *zobi)
{
    zobi->data = malloc((12*64)*sizeof(ZobristBitstrings));
}

void zobrist_bitstrings_generate(ZobristBitstrings *zobi)
{
    if(zobi->data == NULL) return;
    random_generator_seed();
    for(int i = 0; i < (12*64); i++)
    {
        zobi->data[i] = random_generator_get_int();
    }
}

void zobrist_bitstrings_destroy(ZobristBitstrings *zobi)
{
    free(zobi->data);
}

int zobrist_get_hash_key(Board *brd, ZobristBitstrings *zobi)
{

}
