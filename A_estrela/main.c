#include "A_estrela.c"
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


int main(int ac, char** av)
{
    int m =  stoi(av[1]), n = stoi(av[2]), i = 0, j = 0;
    Node matriz[m][n];

    A_estrela(m, n, matriz, i, j);
    

    return 0;
}