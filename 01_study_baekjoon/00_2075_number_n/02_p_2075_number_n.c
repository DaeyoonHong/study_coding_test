#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef long element_type;
typedef struct tag_heap_node
{
    element_type data;
} heap_node;
typedef struct tag_heap
{
    heap_node *nodes; /* heap_node 를 요소로 갖는 배열 (heap_node 포인터를 요소로 갖는 것이 아님) */
    int capacity;
    int used_size;
} heap;

heap *heap_create(int initialize);
void heap_destroy(heap *h);
void heap_insert(heap *h, element_type new_data);
void heap_delete_min(heap *h, heap_node *root);
int heap_get_parent(int index);
int heap_get_left_child(int index);
void heap_swap_nodes(heap *h, int idx1, int idx2);
int compare_nodes(const void *elem1, const void *elem2);

heap *heap_create(int initialize)
{
    heap *new_heap = (heap *)malloc(sizeof(heap));
    new_heap->capacity = initialize;
    new_heap->used_size = 0;
    new_heap->nodes = (heap_node *)malloc(sizeof(heap_node) * new_heap->capacity);
    /* heap_node 를 요소로 갖는 배열 (heap_node 포인터를 요소로 갖는 것이 아님) */
    return new_heap;
}
void heap_destroy(heap *h)
{
    free(h->nodes);
    free(h);
}
void heap_insert(heap *h, element_type new_data)
{
    if(h->used_size == h-> capacity) /* 힙이 가득 찬 경우 (힙에 N개의 데이터가 저장된 경우) */
    {
        if(new_data > h->nodes[0].data)
        {
            heap_node *root = (heap_node *)malloc(sizeof(heap_node));
            heap_delete_min(h, root);
            free(root);
        }
        else
        {
            return;
        }
    }
    int current_position = h->used_size;
    int parent_position = heap_get_parent(current_position);

    h->nodes[current_position].data = new_data;

    while(current_position > 0 && h->nodes[parent_position].data > h->nodes[current_position].data)
    {
        heap_swap_nodes(h, current_position, parent_position);
        current_position = parent_position;
        heap_get_parent(current_position);
    }
    h->used_size++;
}
void heap_delete_min(heap *h, heap_node *root)
{
    int parent_position = 0;
    int left_position = 0;
    int right_position = 0;

    memcpy(root, &h->nodes[0], sizeof(heap_node));
    memset(&h->nodes[0], 0, sizeof(heap_node));

    h->used_size--;
    heap_swap_node(h, 0, h->used_size);

    left_position = heap_get_left_child(0);
    right_position = left_position + 1;

    while(1)
    {
        int selected_child = 0;

        /* 자식 노드가 없는 마지막 노드까지 순회하는 경우 비교 종료 */
        if(left_position >= h->used_size)
        {
            break;
        }
        /* 왼쪽 자식노드가 마지막 노드인 경우*/
        if(right_position >= h->used_size)
        {
            selected_child = left_position;
        }
        else /* 자식 노드가 둘 다 있는 경우 */
        {
            if(h->nodes[left_position].data < h->nodes[right_position].data)
            {
                selected_child = left_position;
            }
            else
            {
                selected_child = right_position;
            }
        }

        /* 비교 대상으로 선정된 자식 노드와 부모 노드의 비교 */
        if(h->nodes[selected_child].data < h->nodes[parent_position].data)
        {
            heap_swap_nodes(h, parent_position, selected_child);
            parent_position = selected_child;
        }

        left_position = heap_get_left_child(0);
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
void heap_swap_node(heap *h, int idx1, int idx2)
{
    element_type temp;
    temp = h->nodes[idx1].data;
    h->nodes[idx1].data = h->nodes[idx2].data;
    h->nodes[idx2].data = temp;
}
int compare_node(const void *elem1, const void *elem2)
{
    /* elem1, elem2 : nodes[i], node[i + 1] 의 시작 주소 
     = 구조체 heap_node 의 시작 주소 */
    heap_node *elem_1 = (heap_node *)elem1;
    heap_node *elem_2 = (heap_node *)elem2;

    if(elem_1->data > elem_2->data)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}