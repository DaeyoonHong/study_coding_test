#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    int idx;
} st_node;

st_node stack[10002];
/* stack 길이 선정 이유가 뭘까? */
int stack_idx = -1;

void push(int val, int idx)
{
    stack_idx++;
    stack[stack_idx].val = val;
    stack[stack_idx].idx = idx;
}

bool is_empty()
{
    if (stack_idx < 0)
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

int *solution(int prices[], size_t len)
{
    int *answer = (int *)malloc(sizeof(int) * len);

    push(prices[0], 0);
    for (int i = 1; i < len; i++)
    {
        int price = prices[i];
        if (top() > price)
        {
            while (!empty() && top() > price)
            {
                st_node temp = pop();
                answer[temp.idx] = i - temp.idx;
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
        answer[temp.idx] = len - 1 - temp.idx;
    }

    return answer;
}