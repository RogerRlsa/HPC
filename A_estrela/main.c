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
            matriz[i][j].pai = NULL;
            if ((i>20 && i<m-20) && (j==36))
            {
                matriz[i][j].andavel = 0;
            }
            //printf("%d ",matriz[i][j].id);
        }
        //printf("\n");
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

void printCaminho(int m, int n, Node M[m][n], Node* no)
{
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", M[i][j].id);
        }
        printf("\n");
    }
    printf("\n");
    while (no->pai)
    {
        printf("%d - ", no->id);
        no = no->pai;
    }
    
}

int main(int ac, char** av)
{
    int m =  atoi(av[1]), n = atoi(av[2]);
    int nT = 4;
    Node matriz[m][n];

    srand(234141);
    int i = rand()%m;
    int j = rand()&n;

    int fim = criarMatriz(m, n, matriz);

    printMatriz(m,n,matriz,fim,i,j);

    omp_set_num_threads(nT);
    Node* no = A_estrela_parallel(m, n, matriz, i, j, fim);
    
    printCaminho(m,n,matriz, no);

    no = A_estrela_seq(m, n, matriz, i, j, fim);
    
    printCaminho(m,n,matriz, no);

    return 0;
}