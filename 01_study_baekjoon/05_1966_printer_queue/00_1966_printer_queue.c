/***************************
 * include libraries
 ***************************/
#include <stdio.h>
#include <stdlib.h>

/***************************
 * define datatypes
 ***************************/
typedef struct q_node
{
    struct q_node *next;
    int priority;
    int index;
} q_node;

int t_num = 0;

/***************************
 * function prototypes
 ***************************/
q_node *create_node(int priority, int index);
void add_node(q_node **queue, q_node *new_node);
int compare(const void *elem1, const void *elem2);
void send_back(q_node **queue);
int is_max(q_node *queue);
void pop(q_node **queue);

/***************************
 * main function
 ***************************/
int main(void)
{
    scanf("%d", &t_num);
    q_node **queue = (q_node **)malloc(sizeof(q_node *) * t_num);

    int *f_num = (int *)malloc(sizeof(int) * t_num);
    int *m = (int *)malloc(sizeof(int) * t_num);
    int p = 0;


    for(int i = 0; i < t_num; i++)
    {
        scanf("%d %d", &f_num[i], &m[i]);
        for(int j = 0; j < f_num[i]; j++)
        {
            scanf("%d", &p);
            q_node *new_node = create_node(p, j);
            add_node(&queue[i], new_node);
        }
    }

    for(int i = 0; i < t_num; i++)
    {
        int ans = 1;
        while(1)
        {

            if(is_max(queue[i]) == 1)
            {
                q_node *current = queue[i];

                if(current->index == m[i])
                {
                    break;
                }
                else
                {
                    pop(&queue[i]);
                    ans++;
                }
            }
            else
            {
                send_back(&queue[i]);
            }
        }
        printf("%d\n", ans);
    }


    free(m);
    free(f_num);
    for(int i = 0; i < t_num ; i++)
    {
        q_node *current = queue[i];
        while(current != NULL)
        {
            q_node *temp = current->next;
            free(current);
            current = temp;
        }
    }
    free(queue);
    return 0;
}

/****************************
 * define functions
 ****************************/
q_node *create_node(int priority, int index)
{
    q_node *new_node = (q_node *)malloc(sizeof(q_node));
    new_node->priority = priority;
    new_node->index=index;
    new_node->next = NULL;

    return new_node;
}
void add_node(q_node **queue, q_node *new_node)
{
    /* 포인터 복사 연산 헷갈림 */
    if((*queue) == NULL)
    {
        (*queue) = new_node;
    }
    else
    {
        q_node *current = (*queue);
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}
int is_max(q_node *queue)
{ 
    q_node *head = queue;
    q_node *current = queue->next;
    while(current != NULL)
    {
        if(current->priority > head->priority)
        {
            return 0;
        }
        current = current->next;
    }
    return 1;
}
void pop(q_node **queue)
{
    q_node *temp = (*queue);
    (*queue) = (*queue)->next;
    free(temp);
}
void send_back(q_node **queue)
{
    q_node *temp = (*queue);
    (*queue) = (*queue)->next;

    q_node *current = (*queue);
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = temp; /* 꼬리로 보낼 때 포인터 초기화 */
    temp->next = NULL;
}
/*
int compare(const void *elem1, const void *elem2)
{
    q_node *compare1= (q_node *)elem1;
    q_node *compare2= (q_node *)elem2;

    if(compare1->priority > compare2->priority)
    {
        return -1;
    }
    else if(compare1->priority < compare2->priority)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
*/