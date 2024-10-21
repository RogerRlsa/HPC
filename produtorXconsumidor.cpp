#include <omp.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

#define nThreads 2
#define N 10

omp_lock_t cheio;
omp_lock_t vazio;

void produtor(int n, int itens[])
{
    int f = 0;
    while (true)
    {

        omp_set_lock(&vazio);

        itens[f] = 1;
        f = (f+1)%n;

        usleep(100000);
        int pos = (f==0)? f:f-1;
        cout << "Produtor: posição " << pos << " -> " << itens[pos] << endl;

        if (f != 0)
        {
            omp_unset_lock(&vazio);
        }else{
            omp_unset_lock(&cheio);
        }

    }
}

void consumidor(int n, int itens[])
{
    int f = 0;
    while (true)
    {

        omp_set_lock(&cheio);

        itens[f] = 0;
        f = (f+1)%n;

        usleep(100000);
        int pos = (f==0)? f:f-1;
        cout << "Consumidor: posição " << pos << " -> " << itens[pos] << endl;

        if (f!=0)
        {
            omp_unset_lock(&cheio);
        }else{
            omp_unset_lock(&vazio);
        }
        
    }
}

int main(void)
{
    int n = N;
    int itens[n];
    memset(itens, 0, n*sizeof(int));

    omp_set_num_threads(nThreads);

    omp_init_lock(&cheio);
    omp_init_lock(&vazio);

    omp_set_lock(&cheio);

#pragma omp parallel shared(n, itens)
{
    #pragma omp sections nowait
    {
        #pragma omp section
        {
            produtor(n, itens);
        }
        #pragma omp section
        {
            consumidor(n, itens);
        }
    }
}

    omp_destroy_lock(&vazio);
    omp_destroy_lock(&cheio);

    return 0;
}