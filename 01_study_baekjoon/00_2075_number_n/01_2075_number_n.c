/***************************
 * 힙을 구현하여 상위 다섯개 데이터만 저장
 ***************************/

/**************************
 * include libraries
 **************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/**************************
 * define datatypes
 **************************/
typedef int element_type;
typedef struct tag_heap_node
{
    element_type data;
}heap_node;
typedef struct tag_heap
{
    heap_node * nodes;
    int capacity;
    int used_size;
}heap;
/**************************
 * function prototype
 **************************/
heap * heap_create(int initialize);
void heap_destroy(heap * h);
void heap_insert(heap * h, element_type new_data);
void heap_delete_min(heap * h, heap_node * root);
int heap_get_parent(int index);
int heap_get_left_child(int index);
void heap_swap_nodes(heap * h, int idx1, int idx2);
int compare_nodes(const void * elem1, const void * elem2);

/*************************
 * main function
 *************************/
int main(void)
{
    int n = 0;

    scanf("%d", &n);
    heap * h = heap_create(n + 1);

    int data = 0;
    for(int i = 0 ; i < n * n ; i++)
    {
        scanf("%d", &data);
        heap_insert(h, data);
    }
    
    qsort(h -> nodes, n + 1, sizeof(heap_node), compare_nodes);
    printf("%d", h -> nodes[n - 1].data);
    heap_destroy(h);

    return 0;
}

/**************************
 * define function
 **************************/
heap * heap_create(int initialize)
{
    heap * new_heap = (heap *)malloc(sizeof(heap));
    new_heap ->  capacity = initialize;
    new_heap -> used_size = 0;
    new_heap -> nodes = (heap_node *)malloc(sizeof(heap_node) * new_heap -> capacity);

    return new_heap;
}

void heap_destroy(heap * h)
{
    free(h -> nodes);
    free(h);
}

void heap_insert(heap * h, element_type new_data)
{
    int current_position = h -> used_size;
    int parent_position = heap_get_parent(current_position);

    h -> nodes[current_position].data = new_data;

    while(current_position > 0 && h -> nodes[current_position].data < h -> nodes[parent_position].data)
    {
        heap_swap_nodes(h, current_position, parent_position);
        current_position = parent_position;
        parent_position = heap_get_parent(current_position);
    }
    h -> used_size++;

    if(h -> used_size == h -> capacity)
    {
        heap_node * root = (heap_node *)malloc(sizeof(heap_node));
        heap_delete_min(h, root);
        free(root);
    }
}

void heap_delete_min(heap * h, heap_node * root)
{
    int parent_position = 0;
    int left_position = 0;
    int right_position = 0;

    memcpy(root, &h -> nodes[0], sizeof(heap_node));
    memset(&h -> nodes[0], 0, sizeof(heap_node));

    h -> used_size--;
    heap_swap_nodes(h, 0, h -> used_size);

    left_position = heap_get_left_child(0);
    right_position = left_position + 1;

    while(1)
    {
        int selected_child = 0;

        if(left_position >= h -> used_size)
        {
            break;
        }
        if(right_position >= h -> used_size)
        {
            selected_child = left_position;
        }
        else
        {
            if(h -> nodes[left_position].data < h -> nodes[right_position].data)
            {
                selected_child = left_position;
            }
            else
            {
                selected_child = right_position;
            }
        }
        if(h -> nodes[selected_child].data < h -> nodes[parent_position].data)
        {
            heap_swap_nodes(h, parent_position, selected_child);
            parent_position = selected_child;
        }
        else
        {
            break;
        }
        left_position = heap_get_left_child(parent_position);
        right_position = left_position + 1;
    }
}

int heap_get_parent(int index)
{
    return (int)((index - 1) / 2);
}
int heap_get_left_child(int index)
{
    return (2 * index) + 1;
}

void heap_swap_nodes(heap * h, int idx1, int idx2)
{
    element_type temp;
    temp = h -> nodes[idx1].data;
    h-> nodes[idx1].data = h -> nodes[idx2].data;
    h -> nodes[idx2].data = temp;
}

int compare_nodes(const void * elem1, const void * elem2)
{
    heap_node * elem_1 = (heap_node *) elem1;
    heap_node * elem_2 = (heap_node *) elem2;

    if(elem_1 -> data > elem_2 -> data)
    {
        return -1;
    }
    else if(elem_1 -> data < elem_2 -> data)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}