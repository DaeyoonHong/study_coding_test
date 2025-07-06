/********************************
 * include libraries
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/********************************
 * define datatypes
 ********************************/
typedef struct tag_stack
{
    int *stack;
    int top;
    int capacity;
} st_stack;

/********************************
 * functions prototypes
 ********************************/
void push(st_stack *stack, int data);
int pop(st_stack *stack);
int size(st_stack *stack);
int empty(st_stack *stack);
int top(st_stack *stack);
st_stack *create_stack(int capacity);
void destroy_stack(st_stack *stack);
int string_to_code(char *cmd);

/********************************
 * main function
 ********************************/
int main (void)
{
    int capacity;
    scanf("%d", &capacity);
    
    st_stack *stack = create_stack(capacity);

    char cmd[6];
    int code;
    int data;
    int result;

    for(int i = 0; i < capacity; i++)
    {
        scanf("%s", cmd);
        code = string_to_code(cmd);
    
        if(code == 1)
        {    
            scanf("%d", &data);
        }
      
        switch(code)
        {
            case 1:
                push(stack, data);
                break;
            case 2:
                result = pop(stack);
                printf("%d\n", result);
                break;
            case 3:
                result = size(stack);
                printf("%d\n", result);
                break;
            case 4:
                result = empty(stack);
                printf("%d\n", result);
                break;
            case 5:
                result = top(stack);
                printf("%d\n", result);
                break;
        }
    }

    destroy_stack(stack);

    return 0;
}

/*******************************
 * define functions
 *******************************/
void push(st_stack *stack, int data)
{
    stack->stack[stack->top++] = data;
}
int pop(st_stack *stack)
{
    int ans = -1;
    if(stack->top == 0)
    {
        /* nothing */
    }
    else
    {
        ans = stack->stack[stack->top - 1];
        stack->top--; /* top 이 가리키는 인덱스는 빈 인덱스이다. */
    }

    return ans;
}
int size(st_stack *stack)
{
    return stack->top;
}
int empty(st_stack *stack)
{
    if(stack->top == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int top(st_stack *stack)
{
    if(stack->top == 0)
    {
        return -1;
    }
    else
    {
        return stack->stack[stack->top - 1];
    }
}
st_stack *create_stack(int capacity)
{
    st_stack *new_stack = (st_stack *)malloc(sizeof(st_stack));
    new_stack->stack = (int *)malloc(sizeof(int) * capacity);
    new_stack->capacity = capacity;
    new_stack->top = 0;

    return new_stack;
}
void destroy_stack(st_stack *stack)
{
    free(stack->stack);
    free(stack);
}
int string_to_code(char *cmd)
{
    if(strcmp(cmd, "push") == 0)  return 1;
    if(strcmp(cmd, "pop") == 0)   return 2;
    if(strcmp(cmd, "size") == 0)  return 3;
    if(strcmp(cmd, "empty") == 0) return 4;
    if(strcmp(cmd, "top") == 0)   return 5;

    return 0;
}