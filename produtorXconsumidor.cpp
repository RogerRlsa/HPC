#include <omp.h>
#include <cstring>

#define nThreads 2
#define N 10

omp_lock_t mutex;
omp_lock_t cheio;
omp_lock_t vazio;

void produtor(int n, int itens[])
{
    int f = 0;
    while (true)
    {

        omp_set_lock(&vazio);

        f = (f+1)%n;
        itens[f] = 1;

        omp_unset_lock(&cheio);

    }
}

void consumidor(int n, int itens[])
{
    int f = 0;
    while (true)
    {

        omp_set_lock(&cheio);

        f = (f+1)%n;
        itens[f] = 0;

        omp_unset_lock(&vazio);

    }
}

int main(void)
{
    int n = N;
    int itens[n];
    memset(itens, 0, n);

    omp_set_num_threads(nThreads);

    omp_init_lock(&mutex);
    omp_init_lock(&cheio);
    omp_init_lock(&vazio);

    omp_set_lock(&cheio);

#pragma omp parallel shared(n, itens)
{
    #pragma omp sections nowait
    {
        #pragma section
        {
            produtor(n, itens);
        }
        #pragma section
        {
            consumidor(n, itens);
        }
    }
}

    omp_destroy_lock(&vazio);
    omp_destroy_lock(&cheio);
    omp_destroy_lock(&mutex);

    return 0;
}