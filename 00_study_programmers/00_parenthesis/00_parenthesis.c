/***********************
 * memo
 * 입력 : 널포인터가 나올때까지 while 문 실행
 * 데이터 저장 : FIFO - linked queue
 * 출력 : printf("s", "true");
 * 연산 : '(' 가 나오면 스택에 삽입, ')' 가 나오면 스택에서 '(' 한 개 삭제
 * *********************/

/************************
 * include headers
 ************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************
 * declare datatypes
 ************************/
typedef struct tag_node
{
    char data;
    struct tag_node * next_node;
}q_node;
typedef struct tag_linked_queue
{
    q_node * head;
    int count;
}linked_queue;

#define DEBUG_OFF 0
#define DEBUG_ON 1
/************************
 * functions
 ************************/
void lq_create_queue(linked_queue ** queue);
void lq_destroy_queue(linked_queue * queue);
q_node * lq_create_node(char new_data);
void lq_destroy_node(q_node * node);
void lq_enqueue(linked_queue * queue, q_node * new_node);
q_node * lq_dequeue(linked_queue * queue);
int lq_is_empty(linked_queue * queue);

/************************
 * main function
 ************************/
int main(void) 
{
    linked_queue * queue;
    lq_create_queue(&queue);
    int p_left = 0;
    char c;
    int error = 0;

    scanf("%1c", &c);
    while(c != '\n' && c != EOF)
    {
        q_node * new_node = lq_create_node(c);
        lq_enqueue(queue, new_node);

        scanf("%1c", &c);
    }
    q_node * print_node = queue -> head;
    #if DEBUG_OFF
    while(print_node != NULL)
    {   
        //printf("here");
        printf("%c  ", print_node -> data);
        print_node = print_node -> next_node;
    }
    #endif

    q_node * current_node = queue -> head;
    while(current_node != NULL)
    {
        if(current_node -> data == '(')
        {
            p_left++;
        }
        else if(current_node -> data == ')')
        {
            if(p_left <= 0)
            {
                error = 1;
                break;
            }        
            else
            {
                p_left--;
            }
        }
        current_node = current_node -> next_node;
    }
    #if DEBUG_OFF
    printf("p_left : %d\n", p_left);
    printf("error : %d\n", error);
    #endif

    lq_destroy_queue(queue);
    if(p_left == 0 && error == 0)
    {
        //printf("true");
        return true;
    }
    else
    {
        //printf("false");
        return false;
    }
}

 /***********************
  * declare functions
  ***********************/
void lq_create_queue(linked_queue ** queue)
{
    (*queue) = (linked_queue *)malloc(sizeof(linked_queue));
    (*queue) -> head = NULL;
    (*queue) -> count = 0;
}
void lq_destroy_queue(linked_queue * queue)
{
    while(!lq_is_empty(queue))
    {
        q_node * popped = lq_dequeue(queue);
        lq_destroy_node(popped);
    }
    free(queue);
}
q_node * lq_create_node(char new_data)
{
    q_node * new_node = (q_node *)malloc(sizeof(q_node));
    new_node -> data = new_data;
    #if 0
    new_node -> data = (char *)malloc(sizeof(char) * (strlen(new_data) + 1))
    #endif
    new_node -> next_node = NULL;

    return new_node;
}
void lq_destroy_node(q_node * node)
{
    free(node);
}
void lq_enqueue(linked_queue * queue, q_node * new_node)
{
    if(queue -> head == NULL)
    {
        queue -> head = new_node;
    }
    else
    {
        q_node * current_node = queue -> head;
        while(current_node -> next_node != NULL)
        {
            current_node = current_node -> next_node;
        }
        current_node -> next_node = new_node;
    }
    queue -> count++;
}
q_node * lq_dequeue(linked_queue * queue)
{
    q_node * front = queue -> head;

    if(queue -> head -> next_node == NULL)
    {
        queue -> head = NULL;
    }
    else
    {
        queue -> head = queue -> head -> next_node;
    }
    queue -> count--;

    return front;
}
int lq_is_empty(linked_queue * queue)
{
    return (queue -> head == NULL);
}