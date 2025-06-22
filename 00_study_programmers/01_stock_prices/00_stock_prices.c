/***********************************
 * include libraies
 ***********************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/***********************************
 * main function
 ***********************************/

// prices_len은 배열 prices의 길이입니다.
int* solution(int prices[], size_t prices_len) 
{
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(int) * prices_len);
    
    /* 간단한 문제이긴 한데 이게 왜 스택과 큐? */
    for(int i = 0 ; i < prices_len ; i++)
    {   
        int sec = 1;
        while((prices[i] <= prices[i + sec]) && (i + sec < prices_len - 1))
        {
            sec++;
        }
        answer[i] = sec;
        answer[prices_len - 1] = 0;
    }
    
    return answer;
}