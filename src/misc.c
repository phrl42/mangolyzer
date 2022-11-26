#include "../include/misc.h"

int miscRand(int min, int max)
{
    int diff = max - min;
    // stackoverflow magic
    return (int)(((double)(diff + 1) / RAND_MAX) * rand() + min); // math is powerful / useful(!!)
}

