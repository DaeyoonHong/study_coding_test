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
 * main function
 ************************/
bool solution(const char* s) 
/* 어떻게 입력받는건지 잘 모르겠다. */
/* 함수 인자로 넘겨준다는 소리 */ 
{
    int p_left = 0;
    int error = 0;
    int index = 0;

    while(s[index] != '\0')
    {
        if(s[index] == '(')
        {
            p_left++;
        }
        else if(s[index] == ')')
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
        index++;
    }
    #if DEBUG_OFF
    printf("p_left : %d\n", p_left);
    printf("error : %d\n", error);
    #endif

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
