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
    int priority;
    int prerequest;
} st_node;

/*****************************
 * function prototypes
 *****************************/
int check_prerequest(st_node *problems, int idx);
int compare_priority(const void *problem1, const void *problem2);

/*****************************
 * main function
 *****************************/
int main(void)
{
    int num_of_problems, num_of_prerequests;
    
    scanf("%d %d", &num_of_problems, &num_of_prerequests);
    
    st_node *problems = (st_node *)malloc(sizeof(st_node) * num_of_problems);
    
    for (int i = 0; i < num_of_problems; i++)
    {
        problems[i].number = i + 1;
        problems[i].priority = 0;
        problems[i].prerequest = 0;
    }
    
    for (int i = 0; i < num_of_prerequests; i++)
    {
        int before;
        int after;
        
        scanf("%d %d", &before, &after);
        
        problems[after - 1].prerequest = before - 1;
    }
    
    int priority = 1;
    for (int i = 0; i < num_of_problems; i++)
    {
        if (problems[i].priority == 0)
        {
            if (check_prerequest(problems, i) == 1)
            {
                problems[i].priority = priority++;
                i = 0;
            }
            else
            {
                /* nothing */
            }
        }
    }
    
    qsort(problems, num_of_problems, sizeof(st_node), compare_priority);
    
    for (int i = 0; i < num_of_problems; i++)
    {
        printf("%d ", problems[i].number);
    }
    printf("\n");
    for (int i = 0; i < num_of_problems; i++)
    {
        printf("%d ", problems[i].priority);
    }
    
    return 0;
}

/*****************************
 * define functions
 *****************************/
int check_prerequest(st_node *problems, int idx)
{
    int rtn = 0;
    int prerequest = problems[idx].prerequest;
    if (prerequest == 0)
    {
        rtn = 1;
    }
    else if (problems[prerequest].priority != 0)
    {
        rtn = 1;
    }
    else
    {
        rtn = 0;
    }
    
    return rtn;
}

int compare_priority(const void *problem1, const void *problem2)
{
    int rtn = 0;
    
    st_node *pro1 = (st_node *)problem1;
    st_node *pro2 = (st_node *)problem2;
    
    if (pro1->priority > pro2->priority)
    {
        rtn = 1;
    }
    else if (pro1->priority < pro2->priority)
    {
        rtn = -1;
    }
    else
    {
        rtn = 0;
    }
    
    return rtn;
}