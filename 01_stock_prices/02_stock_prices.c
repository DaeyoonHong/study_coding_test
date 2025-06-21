/***************************
 * include libraies
 ***************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**************************
 * define datatypes
 **************************/
typedef struct node
{
    int val;
    int idx;
} st_node;

st_node stack[10002];
int stack_idx = -1;

/**************************
 * delcare functions
 **************************/
void push(int val, int idx)
{
    stack_idx++; /* pop, empty, push 함수에서 인덱스 정보를 이용해 스택 컨트롤 */
    stack[stack_idx].val = val;
    stack[stack_idx].idx = idx; 
    /* 여기서 저장하는 인덱스는 prices 배열에서의 위치를 나타냄, 내리지 않은 시간 계산에 사용 */
}

bool is_empty()
{
    if(stack_idx < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int top()
{
    return stack[stack_idx].val;
}

st_node pop()
{
    return stack[stack_idx--];
}

/****************************
 * main function
 ****************************/
int * solution(int prices[], size_t len)
{
    int * answer = (int * )malloc(sizeof(int) * len);
    
    push(prices[0], 0);
    for(int i = 1 ; i < len ; i++)
    {
        int price = prices[i];
        if(top() > price) /* 가격이 내린 경우 */
        { 
            while(!empty() && top() > price)
            {
                st_node temp = pop();
                answer[temp.idx] = i - temp.idx; /* 내리지 않은 시간 계산 */
            }
            push(price, i);
        }
        else
        {
            push(price, i);
        }
    }

    while(!empty())
    {
        st_node temp = pop();
        answer[temp.idx] = (len - 1) - temp.idx; /* 끝까지 안내린 가격들 유지 시간 계산 */
    }

    return answer;
}