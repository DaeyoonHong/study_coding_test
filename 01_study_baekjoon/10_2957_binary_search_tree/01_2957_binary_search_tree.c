/***********************************
 * include libraries
 ***********************************/
#include <stdio.h>
#include <stdlib.h>

/***********************************
 * include datatypes
 ***********************************/
int c;
typedef struct  tag_node
{
    int data;
    int depth;
} st_node;

/***********************************
 * function prototypes
 ***********************************/
int calculate_depth(st_node *x, int i);
int compare(const void *element1, const void *element2);


/**********************************
 * main function
 **********************************/
int main(void)
{
    int n;
    int c = 0;

    scanf("%d", &n);
    st_node *x = (st_node *)malloc(sizeof(st_node) * n);
    int *depth =(int *)malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++)
    {
        x[i].depth = -1;
        x[i].data = -1;

        scanf("%d" ,&x[i].data);
        c += calculate_depth(x, i);
        printf("%d\n", c);
    }

    free(x);
    return 0;
}

/*************************************
 * define functions
 *************************************/
int calculate_depth(st_node *x, int i)
{
    if(i == 0)
    {
        x[i].depth = 0;
        return 0;
    }

    qsort(x, i + 1, sizeof(st_node), compare); /* 정렬을 한번만 해야될듯 */

    int idx = 0;
    while(x[idx].depth != -1)
    {
        idx++;
    }
   
    if(idx - 1 < 0)
    {
        x[idx].depth = x[idx + 1].depth + 1;
    }
    else if(idx + 1 > i)
    {
        x[idx].depth = x[idx - 1].depth + 1;
    }
    else
    {
        if(x[idx - 1].depth > x[idx + 1].depth)
        {
            x[idx].depth = x[idx - 1].depth + 1;
        }
        else
        {
            x[idx].depth = x[idx + 1].depth + 1;
        }
    }

    return x[idx].depth;
}
int compare(const void *element1, const void *element2)
{
    st_node *elem1 = (st_node *)element1;
    st_node *elem2 = (st_node *)element2;

    if(elem1->data > elem2->data)
    {
        return 1;
    }
    else if(elem1->data < elem2->data)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
