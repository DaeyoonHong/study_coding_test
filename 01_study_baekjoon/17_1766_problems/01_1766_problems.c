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
    int number;
    struct tag_node *next;
} st_node;

typedef struct tag_min_heap_node
{
    int *problems;
    int cnt;
} st_min_heap;

/*****************************
 * function prototypes
 *****************************/
st_node *create_node(int number);
void add_node(st_node **problems, int idx, st_node *new_node);
void print_node(st_node **problems, int idx, int *depth);
void push(st_min_heap *min_heap, int problem_num);
int get_parent(int current);
int pop(st_min_heap *min_heap);
int get_left_child(int current);

/*****************************
 * main function
 *****************************/
int main(void)
{
    int num_of_problems;
    int num_of_prerequests;
    scanf("%d %d", &num_of_problems, &num_of_prerequests);
    
    int size_of_problems = num_of_problems + 1;
    
    st_node **problems = (st_node **)malloc(sizeof(st_node *) * size_of_problems);  
    int * depth = (int *)malloc(sizeof(int) * size_of_problems);
    for (int i = 1; i < size_of_problems; i++)
    {
        problems[i] = NULL;
        depth[i] = 0;
    }
    
    
    int before;
    int after;
    for (int i = 0; i < num_of_prerequests; i++)
    {
        scanf("%d %d", &before, &after);
        
        st_node *new_node = create_node(after);
        add_node(problems, before, new_node); /* number 작은 순서대로 넣기 */
        
        depth[after]++;
    }
    
    /* depth 가 0인 node 이용하여 최소 힙 구성 */
    st_min_heap *min_heap = (st_min_heap *)malloc(sizeof(st_min_heap));
    min_heap->problems = (int *)malloc(sizeof(int) * size_of_problems);
    min_heap->cnt = 0;
    
    for (int i = 1; i < size_of_problems; i++)
    {
        if (depth[i] == 0)
        {
            push(min_heap, i);
        }
    }
    
    /* head 제거 후 최소 힙 업데이트 */
    int printed_cnt = 0;
    while (printed_cnt < num_of_problems)
    {
        int popped = pop(min_heap);
        printf("%d ", popped);
        printed_cnt++;
        
        st_node *current = problems[popped];
        while (current != NULL)
        {
            depth[current->number]--;
            if (depth[current->number] == 0)
            {
                push(min_heap, current->number);
            }
            current = current->next;
        }
    }
    
    free(depth);
    for (int i = 0; i < size_of_problems; i++)
    {
        if (problems[i] != NULL)
        {
            st_node *current = problems[i];

            while (current != NULL)
            {
                st_node *temp = current->next;
                free(current);
                current = temp;
            }        
        }
    }
    free(problems);
    
    return 0;
}

/*****************************
 * define functions
 *****************************/
st_node *create_node(int number)
{
    st_node *new_node = (st_node *)malloc(sizeof(st_node));
    
    new_node->number = number;
    new_node->next = NULL;
    
    return new_node;
}

void add_node(st_node **problems, int idx, st_node *new_node)
{
    if (problems[idx] == NULL)
    {
        problems[idx] = new_node;
    }
    else
    {
        st_node *current = problems[idx];
        
        if(current->number > new_node->number)
        {
            problems[idx] = new_node;
            new_node->next = current;
        }
        else
        {
            while (current->next != NULL)
            {
                if (current->next->number > new_node->number)
                {
                    break;
                }
                current = current->next;
            }   
            st_node *temp = current->next;
            current->next = new_node;
            new_node->next = temp;
        }
    }
}

void push(st_min_heap *min_heap, int problem_num)
{
    min_heap->problems[min_heap->cnt++] = problem_num;
    
    int current = min_heap->cnt - 1;
    int parent = get_parent(current);
    
    while (current > 0)
    {
        if (min_heap->problems[current] < min_heap->problems[parent])
        {
            int temp = min_heap->problems[current];
            min_heap->problems[current] = min_heap->problems[parent];
            min_heap->problems[parent] = temp;
            
            current = parent;
            parent = get_parent(current);
        }
        else
        {
            break;
        }
    }
}

int pop(st_min_heap *min_heap)
{
    int rtn = min_heap->problems[0];
    
    min_heap->problems[0] = min_heap->problems[--min_heap->cnt];
    
    int current = 0;
    int left_child = get_left_child(current);
    int right_child = left_child + 1;
    int selected_child;
    
    while (1)
    {
        if (left_child > min_heap->cnt)
        {
            break;
        }
        else if (left_child == min_heap->cnt)
        {
            selected_child = left_child;
        }
        else if (min_heap->problems[left_child] > min_heap->problems[right_child])
        {
            selected_child = right_child;
        }
        else
        {
            selected_child = left_child;
        }
        
        if (min_heap->problems[selected_child] > min_heap->problems[current])
        {
            break;
        }
        else
        {
            int temp = min_heap->problems[current];
            min_heap->problems[current] = min_heap->problems[selected_child];
            min_heap->problems[selected_child] = temp;
            
            current = selected_child;
            left_child = get_left_child(current);
            right_child = left_child + 1;
        }
    }

    return rtn;
}

int get_left_child(int current)
{
    return current * 2 + 1;
}

int get_parent(int current)
{
    return (current - 1) / 2;
}