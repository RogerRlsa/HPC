#include "A_estrela.c"
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int criarMatriz(int m, int n, Node matriz[m][n])
{
    srand(time(NULL));
    int i = rand()%m;
    int j = rand()&n;
    int fim = j+(i*m);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j].andavel = 1;
            matriz[i][j].dis_percorrida = 0;
            matriz[i][j].id = j+(i*m);
            matriz[i][j].viz = 0;
            if ((i>20 && i<m-20) && (j==36))
            {
                matriz[i][j].andavel = 0;
            }
        }
    }
    return fim;
}

void printMatriz(int m, int n, Node M[m][n], int fim, int ini_i, int ini_j)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(M[i][j].id==fim)
            {
                printf("F");
            }else if(i == ini_i && j == ini_j)
            {
                printf("I");
            }else if (M[i][j].andavel==1)
            {
                printf("A");
            }else
            {
                printf("B");
            }
        }
        printf("\n");
    }
}

int main(int ac, char** av)
{
    int m =  atoi(av[1]), n = atoi(av[2]);
    Node matriz[m][n];

    srand(234141);
    int i = rand()%m;
    int j = rand()&n;

    int fim = criarMatriz(m, n, matriz);

    printMatriz(m,n,matriz,fim,i,j);

    A_estrela(m, n, matriz, i, j, fim);
    

    return 0;
}