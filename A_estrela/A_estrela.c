#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

typedef struct heap_element
    {
        int key;
        int i,j;
        Node* val;
    } Heap_element;

typedef struct heap
{
    int size;
    int vazio;
    Heap_element* list;

} Heap;

typedef struct node
{
    int id;
    int viz;
    int andavel;
    Node* pai;

} Node;

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
        printf("ERRO: HEAP VAZIA!!!");
        return

    *el = h->list[1];
    h->vazio = h->vazio - 1;

    h->list[1] = h->list[h->vazio];
    h->list[h->vazio].key = ;

    int max_pos = 0;
    int pos = 1;
    Heap_element temp;
    while (!max_pos)
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

void add_viz_heap(Heap* h, Heap_element el)
{
    
}

Node* A_estrela(int m, int n, Node** A, int i, int j, int fim)
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
            add_viz_heap(&h, el);
        }
    }
    free(h.list);
    printf("Caminho não encontrado!!!");
}