#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

typedef struct node
{
    int id;
    int viz;
    int dis_percorrida;
    int andavel;
    struct node* pai;

} Node;

typedef struct heap_element
    {
        unsigned int key;
        int i,j;
        Node* val;
    } Heap_element;

typedef struct heap
{
    int size;
    int vazio;
    Heap_element* list;

} Heap;

void push_heap(Heap* h, Heap_element el)
{
    h->list[h->vazio] = el;
    int pos = h->vazio;
    h->vazio = h->vazio+1;

    int min_pos = 0;
    Heap_element temp;
    while (!min_pos && pos>1)
    {
        min_pos = 1;
        if(h->list[pos].key < h->list[pos/2].key)
        {
            temp = h->list[pos];
            h->list[pos] = h->list[pos/2];
            h->list[pos/2] = temp;
            pos = pos/2;
            min_pos = 0;
        }
    }
}

int is_empty(Heap* h)
{
    return (h->vazio == 1)? 1 : 0;
}

void pop_heap(Heap* h, Heap_element* el)
{
    if(is_empty(h))
    {
        printf("ERRO: HEAP VAZIA!!!");
        return;
    }
    *el = h->list[1];
    h->vazio = h->vazio - 1;

    h->list[1] = h->list[h->vazio];
    unsigned int max_val = -1;
    h->list[h->vazio].key = max_val;

    int max_pos = 0;
    int pos = 1;
    Heap_element temp;
    while (!max_pos || (pos*2) >= h->vazio)
    {
        max_pos = 1;
        if(h->list[pos*2].key < h->list[(pos*2)+1].key)
        {
            if(h->list[pos].key < h->list[pos*2].key)
            {
                temp = h->list[pos*2];
                h->list[pos*2] = h->list[pos];
                h->list[pos] = temp;
                pos = pos*2;
                max_pos = 0;
            }
            else if(h->list[pos].key < h->list[(pos*2)+1].key)
            {
                temp = h->list[(pos*2)+1];
                h->list[(pos*2)+1] = h->list[pos];
                h->list[pos] = temp;
                pos = (pos*2)+1;
                max_pos = 0;
            }
        }
    }
}

int heuristica(Heap_element a, Heap_element b)
{
    unsigned int he = 0;
    he = (a.i>b.i)? a.i-b.i : b.i-a.i;
    he += (a.j>b.j)? a.j-b.j : b.j-a.j;
    return he*10;
}

Node* A_estrela(int m, int n, Node A[m][n], int i, int j, int fim)
{
    Heap h;
    h.vazio = 1;
    h.size = (m*n)+1;
    h.list = (Heap_element*) malloc(h.size*sizeof(Heap_element));
    // adicionar o ponto de partida na heap
        
    Heap_element el;
    el.key = 0;
    el.i = i;
    el.j = j;
    el.val = &A[i][j];
    el.val->pai = el.val;
    push_heap(&h, el);

    while(!is_empty(&h))
    {
        pop_heap(&h, &el);

        for(int i=0; i<8; i++)
        {
            if(el.val->id == fim)
            {
                free(h.list);
                printf("Caminho encontrado!!!");
                return el.val;
            }
            el.val->viz = 1;
            
            // Adicionar os vizinhos do nó atual à heap
            for (int j = 0; j < 4; j++)
            {
                Node* vizinho;
                Heap_element viz_el;
                switch (i)
                {
                case 0:
                    if(el.i==0)
                        continue;
                    vizinho = &A[el.i-1][el.j];
                    viz_el.i = el.i-1;
                    viz_el.j = el.j;
                    break;
                case 1:
                    if(el.j==0)
                        continue;
                    vizinho = &A[el.i][el.j-1];
                    viz_el.i = el.i;
                    viz_el.j = el.j-1;
                    break;
                case 2:
                    if(el.i==m-1)
                        continue;
                    vizinho = &A[el.i+1][el.j];
                    viz_el.i = el.i+1;
                    viz_el.j = el.j;
                    break;
                case 3:
                    if(el.j==n-1)
                        continue;
                    vizinho = &A[el.i][el.j+1];
                    viz_el.i = el.i;
                    viz_el.j = el.j+1;
                    break;
                }
                if (vizinho->andavel==1 && (vizinho->id != el.val->pai->id))
                {
                    viz_el.val = vizinho;
                    viz_el.val->pai = el.val;
                    viz_el.key = heuristica(viz_el, el);
                    viz_el.val->dis_percorrida = el.val->dis_percorrida+10;
                    viz_el.key += viz_el.val->dis_percorrida;
                    
                    push_heap(&h, viz_el);
                }
            }
        }
    }
    free(h.list);
    printf("Caminho não encontrado!!!");
    return &A[i][j];
}