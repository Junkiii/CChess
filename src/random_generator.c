//Pascal Schumann & Hendrik Junkawitsch

#include "random_generator.h"

void random_generator_seed()
{
    srand(time(NULL));
}

int random_generator_get_int()
{
    return rand();
}