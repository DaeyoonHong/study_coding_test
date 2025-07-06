/*****************************
 * include libraries
 *****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************
 * define datatypes
 *****************************/
typedef struct tag_queue
{
    int *queue;
    int front;
    int rear;
    int capacity;
} st_queue;
/****************************
 * function prototypes
 ****************************/
st_queue *create_queue(int capacity);
void push(st_queue *q, int data);
int pop(st_queue *q);
int size(st_queue *q);
int empty(st_queue *q);
int front(st_queue *q);
int back(st_queue *q);
int str_to_code(const char *str);
void destroy_queue(st_queue *q);


/****************************
 * main functions
 ****************************/
int main(void)
{
    int n = 0;
    scanf("%d", &n);
    st_queue *q = create_queue(n);

    for(int i = 0; i < n; i++)
    {
        char command[6];
        int cmd;
        int num = 0;
        int result;
        scanf("%s", command);
        cmd = str_to_code(command);
        if(cmd == 1)
        {
            scanf("%d", &num);
        }
        
        switch(cmd)
        {
            case 1:
                push(q, num);
                break;
            case 2:
                result = pop(q);
                printf("%d\n", result);
                break;
            case 3:
                result = size(q);
                printf("%d\n", result);
                break;
            case 4:
                result = empty(q);
                printf("%d\n", result);
                break;
            case 5:
                result = front(q);
                printf("%d\n", result);
                break;
            case 6:
                result = back(q);
                printf("%d\n", result);
                break;
        }
    }

    destroy_queue(q);

    return 0;
}

/****************************
 * define functions
 ****************************/
st_queue *create_queue(int capacity)
{
    st_queue *q = (st_queue *)malloc(sizeof(st_queue));
    q->queue = (int *)malloc(sizeof(int) * capacity);
    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;

    return q;
}
void destroy_queue(st_queue *q)
{
    free(q->queue);
    free(q);
}
void push(st_queue *q, int data)
{
    q->queue[q->rear++] = data;
}
int pop(st_queue *q)
{
    if(q->front != q->rear)
    {
        return q->queue[q->front++];
    }
    else
    {
        return -1;
    }
}
int size(st_queue *q)
{
    return q->rear - q->front;
}
int empty(st_queue *q)
{
    if(q->front != q->rear)
    {
        return 0;
    }
    else
    {
        return 1;
    }}
int front(st_queue *q)
{
    if(q->front != q->rear)
    {
        return q->queue[q->front];
    }
    else
    {
        return -1;
    }
}
int back(st_queue *q)
{
    if(q->front != q->rear)
    {
        return q->queue[q->rear - 1];
    }
    else
    {
        return -1;
    }
}
int str_to_code(const char *str)
{
    if(strcmp(str, "push") == 0) return 1;
    if(strcmp(str, "pop") == 0) return 2;
    if(strcmp(str, "size") == 0) return 3;
    if(strcmp(str, "empty") == 0) return 4;
    if(strcmp(str, "front") == 0) return 5;
    if(strcmp(str, "back") == 0) return 6;

    return 0;
}

