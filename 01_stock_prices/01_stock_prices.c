#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
    int val;
    int idx;
}Node;

Node stack[100002];
int stackIdx = -1;

void push(int val, int idx) {
    stackIdx++;
    stack[stackIdx].val = val;
    stack[stackIdx].idx = idx;
}

bool empty() {
    if (stackIdx < 0) {
        return true;
    }
    else {
        return false;
    }
}

int top() {
    return stack[stackIdx].val;
}

Node pop() {
    return stack[stackIdx--];
}

// prices_len은 배열 prices의 길이입니다.
int* solution(int prices[], size_t len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(int) * len);

    push(prices[0], 0);
    for (int i = 1; i < len; i++) {
        int price = prices[i];
        if (top() > price) {
            while (!empty() && top() > price) {
                Node temp = pop();
                answer[temp.idx] = i - temp.idx;
            }
            push(price, i);
        }
        else {
            push(price, i);
        }
    } 

    while(!empty()) {
        Node temp = pop();
        answer[temp.idx] = len - 1 - temp.idx;
    }

    /*for (int i = 0; i < len; i++) {
        printf("%d ", answer[i]);
    }
    printf("\n");*/

    return answer;
}
