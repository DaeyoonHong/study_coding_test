/*****************************
 * include libraries
 *****************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************
 * define datatypes
 *****************************/
int n;
int idx;

/*****************************
 * function prototypes
 *****************************/
void insert_data(int *array, int data);
int get_parent(int current);
int get_left_child(int parent);
int pop(int *array);

/*****************************
 * main function
 *****************************/
int main(void)
{
    scanf("%d", &n);
    int *array = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++)
    {
        array[i] = 0;
    }

    int data;

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &data);
        if(data != 0)
        {
            insert_data(array, data);    
        }
        else
        {
            printf("%d\n", pop(array));
        }
    }
    
    free(array);
    return 0;
}

/*****************************
 * define functions
 *****************************/
void insert_data(int *array, int data)
{
    array[idx] = data;
    int current = idx;
    int parent;

    while(current >= 0)
    {  
        parent = get_parent(current);
        if(array[parent] > array[current])
        {
            int temp = array[parent];
            array[parent]= array[current];
            array[current] = temp;
            current = parent;
        }
        else
        {
            break;
        }       
    }
    idx++;
}
int get_parent(int current)
{
    return (current - 1) / 2;
}
int get_left_child(int parent)
{
    return parent * 2 + 1;
}
int pop(int *array)
{
    int pop = array[0];
    if(pop == 0)
    {
        return 0;
    }

    idx--;
    array[0] = array[idx];
    array[idx] = 0;

    int parent = 0;
    int left_child;
    int right_child;
    int selected_child;

    while(1)
    {
        left_child = get_left_child(parent);
        right_child = left_child + 1;
        
        if(array[left_child] == 0)
        {
            break;
        }
        else if(array[right_child] == 0)
        {
            selected_child = left_child;
        }
        else if(array[left_child] <= array[right_child])
        {
            selected_child = left_child;
        }
        else
        {
            selected_child = right_child;
        }

        if(array[parent] > array[selected_child])
        {
            int temp = array[parent];
            array[parent] = array[selected_child];
            array[selected_child] = temp;

            parent = selected_child;
        }
        else
        {
            break;
        }        
    }

    return pop;
}
