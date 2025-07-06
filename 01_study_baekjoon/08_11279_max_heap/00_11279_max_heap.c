/*******************************
 * include libraries
 *******************************/
#include <stdio.h>
#include <stdlib.h>

/******************************
 * define datatypes
 ******************************/
typedef struct tag_heap
{
    unsigned int *heap;
    int capacity;
    int rear;
} st_heap;

/*****************************
 * function prototypes
 *****************************/
st_heap *create_heap(int capacity);
void destroy_heap(st_heap *h);
void add(st_heap *h, unsigned int data);
void swap(st_heap *h, int parent, int child);
int compare_data(st_heap *h, int parent, int child);
unsigned int pop(st_heap *h);
int get_parent(int index);
int get_left_child(int index);

 /****************************
  * main function
  ****************************/
int main(void)
{
    int n;
    unsigned int x;
    unsigned int p;

    scanf("%d", &n);
    st_heap *h = create_heap(n);

    for(int i = 0; i < n; i++)
    {
        scanf("%u", &x);
        if(x == 0)
        {
            p = pop(h);
            printf("%u\n", p);
        }
        else
        {
            add(h, x);
        }
    }

    destroy_heap(h);
    return 0;
}

/*****************************
 * define functions
 *****************************/
st_heap *create_heap(int capacity)
{
    st_heap *h = (st_heap *)malloc(sizeof(st_heap));
    h->heap = (unsigned int *)malloc(sizeof(unsigned int) * capacity);
    for(int i = 0; i < capacity; i++)
    {
        h->heap[i] = 0;
    }
    h->capacity = capacity;
    h->rear = 0;

    return h;
}
void destroy_heap(st_heap *h)
{
    free(h->heap);
    free(h);
}
void add(st_heap *h, unsigned int data)
{
    int current = h->rear;
    h->heap[h->rear++] = data;

    while(current > 0)
    {
        int parent = get_parent(current);

        if(compare_data(h, parent, current) == 1)
        {
            swap(h, parent, current);
        }
        else
        {
            break;
        }
        current = parent;
    }
}
void swap(st_heap *h, int parent, int child)
{
    int temp = h->heap[parent];
    h->heap[parent] = h->heap[child];
    h->heap[child] = temp;
}
int compare_data(st_heap *h, int parent, int child)
{
    if(h->heap[parent] > h->heap[child])
    {
        return -1;
    }
    else if(h->heap[parent] < h->heap[child])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
unsigned int pop(st_heap *h)
{
    unsigned int pop = h->heap[0];
    if(pop == 0) return pop;

    h->heap[0] = h->heap[h->rear - 1];
    h->heap[h->rear - 1] = 0;
    h->rear--;

    int current = 0;
    int left_child, right_child, selected_child;

    while(1)
    {
        left_child = get_left_child(current);
        right_child = left_child + 1;

        if(h->heap[left_child] == 0)
        {
            break;
        }
        else if(h->heap[right_child] == 0)
        {
            selected_child = left_child;
        }
        else if(compare_data(h, left_child, right_child) != 1)
        {
            selected_child = left_child;
        }
        else
        {
            selected_child = right_child;
        }

        if(compare_data(h, current, selected_child) != 1)
        {
            break;
        }
        else
        {
            swap(h, current, selected_child);
        }
        current = selected_child;
    }

    return pop;
}
int get_parent(int index)
{
    return (index - 1) / 2;
}

int get_left_child(int index)
{
    return index * 2 + 1;
}