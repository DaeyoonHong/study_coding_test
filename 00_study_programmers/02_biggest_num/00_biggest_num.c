/**************************
 * 입력 : 배열
 * 출력 : 문자열
 * 연산 : 구조체 배열을 생성하여 퀵정렬
 **************************/

/*************************
 * include libraries
 *************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**************************
 * define datatypes
 **************************/
typedef struct node
{
    char * num;
    char first_num;
} st_node;

/**************************
 * function prototypes
 **************************/
void swap(st_node * a, st_node * b);
int partition(st_node * data_set, int left, int right);
void q_sort(st_node * data_set, int left, int right);


/**************************
 * main function
 **************************/

// numbers_len은 배열 numbers의 길이입니다.
char* solution(int numbers[], size_t numbers_len) 
{   
    char* answer = (char*)malloc(sizeof(char) * (4 * numbers_len));
    st_node * st_numbers = (st_node *)malloc(sizeof(st_node) * numbers_len);

    for(int i = 0 ; i < numbers_len ; i++)
    {
        st_numbers[i].num = (char *)malloc(sizeof(char) * 5);

        sprintf(st_numbers[i].num, "%d", numbers[i]);

        st_numbers[i].first_num = st_numbers[i].num[0];
    }

    q_sort(st_numbers, 0, numbers_len - 1);

    /* 문자열 이어 붙히기 */
    int ans_idx = 0;
    for(int i = 0 ; i < numbers_len ; i++)
    {
        int j = 0;
        while(st_numbers[i].num[j] != '\0')
        {
            answer[ans_idx++] = st_numbers[i].num[j++];
        }
    }
    answer[ans_idx] = '\0';

    return answer;
}

/**************************
 * define functions
 **************************/
void swap(st_node * a, st_node * b)
{
    st_node temp = * a;
    * a = * b;
    *b = temp;
}
int partition(st_node * data_set, int left, int right)
{
    int first = left;
    int pivot = data_set[first].first_num;

    ++left;

    while(left <= right)
    {
        while(data_set[left].first_num >= pivot && left < right)
        {
            left++;
        }
        while(data_set[right].first_num <= pivot && left <= right)
        {
            right--;
        }
        if(left < right)
        {
            swap(&data_set[left], &data_set[right]);
        }
        else
        {
            break;
        }
    }
    swap(&data_set[first], &data_set[right]); 
    /* swap 함수 호출 시 주소 연산자를 사용해야 되는 이유를 모르겠다. */
    /* 주소 연산자를 사용하지 않으면 값이 복사되어 원본 데이터가 변경되지 않는다. */
    /* data_set[first] 는 포인터가 아니다. */

    return right;
}
void q_sort(st_node * data_set, int left, int right)
{
    if(left < right)
    {
        int index = partition(data_set, left, right);

        q_sort(data_set, left, index - 1);
        q_sort(data_set, index + 1, right);
    }
}

