/*****************************
 * include libraries
 *****************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************
 * define datatypes
 *****************************/
typedef struct tag_node
{
    int data;
    int abs;
} st_node;

typedef struct tag_queue
{
    st_node **array;
    int cnt;
    int capacity;
} st_queue;

/*****************************
 * function prototypes
 *****************************/
st_queue *create_queue(int capacity);
st_node *create_node(int data);
void add_node(st_queue *queue, st_node *new_node);
int pop(st_queue *queue);
void swap_nodes(st_node *node1, st_node *node2);
int get_parent(int idx);
int get_left_child(int idx);
void destroy_queue(st_queue *queue);

/*****************************
 * main function
 *****************************/
int main(void)
{
    int n;
    int x;

    scanf("%d", &n);
    st_queue *queue = create_queue(n);

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        if(x != 0)
        {
            st_node *new_node = create_node(x);
            add_node(queue, new_node);
        }
        else
        {
            if(queue->cnt == 0)
            {
                printf("0\n");
            }
            else
            {
                printf("%d\n", pop(queue));
            }   
        }
    }
    
    destroy_queue(queue);
    return 0;
}

/*****************************
 * define functions
 *****************************/
st_queue *create_queue(int capacity)
{
    st_queue *queue = (st_queue *)malloc(sizeof(st_queue));
    st_node **array = (st_node **)malloc(sizeof(st_node *) * capacity);
    queue->array = array;
    queue->cnt = 0;
    queue->capacity = capacity;

    return queue;
}
st_node *create_node(int data)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));

    new_node->data = data;
    if(data > 0)
    {
        new_node->abs = data;
    }
    else
    {
        new_node->abs = data * -1;
    }

    return new_node;  
}
void add_node(st_queue *queue, st_node *new_node)
{
    queue->array[queue->cnt] = new_node;

    int current_idx = queue->cnt;
    queue->cnt++;
    int parent_idx;
    
    while(current_idx > 0)
    {
        parent_idx = get_parent(current_idx);

        if(queue->array[current_idx]->abs < queue->array[parent_idx]->abs)
        {
            swap_nodes(queue->array[parent_idx], queue->array[current_idx]);
        }
        else if(queue->array[current_idx]->abs == queue->array[parent_idx]->abs)
        {
            if(queue->array[current_idx]->data < queue->array[parent_idx]->data)
            {
                swap_nodes(queue->array[parent_idx], queue->array[current_idx]);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }    
        current_idx = parent_idx;
    }
}
int pop(st_queue *queue)
{
    int pop = queue->array[0]->data;
    int last_idx = queue->cnt - 1;
    swap_nodes(queue->array[0], queue->array[last_idx]);
    queue->cnt--;

    int current_idx = 0;
    int left_child;
    int right_child;
    int selected_child;

    while(1)
    {
        left_child = get_left_child(current_idx);
        right_child = left_child + 1;

        if(left_child > queue->cnt - 1)
        {
            break;
        }
        else if(right_child > queue->cnt - 1)
        {
            selected_child = left_child;
        } 
        else if(queue->array[left_child]->abs < queue->array[right_child]->abs)
        {
            selected_child = left_child;
        }
        else if(queue->array[left_child]->abs == queue->array[right_child]->abs)
        {
            if(queue->array[left_child]->data < queue->array[right_child]->data)
            {
                selected_child = left_child;
            }
            else
            {
                selected_child = right_child;
            }
        }
        else
        {
            selected_child = right_child;
        }

        if(queue->array[selected_child]->abs < queue->array[current_idx]->abs)
        {
            swap_nodes(queue->array[selected_child], queue->array[current_idx]);
        }
        else if(queue->array[selected_child]->abs == queue->array[current_idx]->abs)
        {
            if(queue->array[selected_child]->data < queue->array[current_idx]->data)
            {
                swap_nodes(queue->array[selected_child], queue->array[current_idx]);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }    
        current_idx = selected_child;
    }

    return pop;
}

void swap_nodes(st_node *node1, st_node *node2)
{
    int temp_data = node1->data;
    int temp_abs = node1->abs;

    node1->abs = node2->abs;
    node1->data = node2->data;
    node2->abs = temp_abs;
    node2->data = temp_data;

}

int get_parent(int idx)
{
    return (idx - 1) / 2;
}
int get_left_child(int idx)
{
    return idx * 2 + 1;
}

void destroy_queue(st_queue *queue)
{
    for(int i = 0; i < queue->capacity; i++)
    {
        if(queue->array[i] != NULL)
        {
            free(queue->array[i]);
        }
    }
    free(queue);
}