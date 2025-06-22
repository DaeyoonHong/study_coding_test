/**************************
 * 입력 : 배열
 * 출력 : 문자열
 * 연산 : 모든 경우의 수 계산 후 정렬
 **************************/

/*************************
 * include libraries
 *************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
void generate_permutations(st_node * numbers, int start, int end, st_node * combinations, int * comb_index);
int factorial(int n);
char* solution(int numbers[], size_t numbers_len);


/**************************
 * main function
 **************************/
int main(void)
{
    int numbers[] = {6, 10, 2};
    char * ans = solution(numbers, 3);
    
    printf("\n=== 최종 결과 ===\n");
    printf("가장 큰 수: %s\n", ans);
    
    free(ans);
    return 0;
}

// numbers_len은 배열 numbers의 길이입니다.
char* solution(int numbers[], size_t numbers_len) 
{   
    char* answer = (char*)malloc(sizeof(char) * (4 * numbers_len));
    st_node * st_numbers = (st_node *)malloc(sizeof(st_node) * numbers_len);

    for(int i = 0 ; i < numbers_len ; i++)
    {
        st_numbers[i].num = (char *)malloc(sizeof(char) * 5);
        sprintf(st_numbers[i].num, "%d", numbers[i]);
    }

    // 모든 경우의 수 계산 (n!)
    int comb_num = factorial(numbers_len);
    
    // 모든 조합을 저장할 배열 생성
    st_node * st_comb = (st_node *)malloc(sizeof(st_node) * comb_num);
    for(int i = 0 ; i < comb_num ; i++)
    {
        st_comb[i].num = (char *)malloc(sizeof(char) * (numbers_len * 4 + 1));
        st_comb[i].num[0] = '\0';  // 빈 문자열로 초기화
    }

    // 모든 순열 생성
    int comb_index = 0;
    generate_permutations(st_numbers, 0, numbers_len - 1, st_comb, &comb_index);

    // 생성된 모든 조합 출력 (디버깅용)
    printf("=== 모든 경우의 수 ===\n");
    for(int i = 0 ; i < comb_num ; i++)
    {
        printf("%d: %s\n", i+1, st_comb[i].num);
    }
    printf("총 %d개의 경우의 수\n", comb_num);

    // 가장 큰 수 찾기
    char* max_num = st_comb[0].num;
    for(int i = 1 ; i < comb_num ; i++)
    {
        if(strlen(st_comb[i].num) > strlen(max_num) || 
           (strlen(st_comb[i].num) == strlen(max_num) && strcmp(st_comb[i].num, max_num) > 0))
        {
            max_num = st_comb[i].num;
        }
    }

    // 결과 복사
    strcpy(answer, max_num);

    // 메모리 해제
    for(int i = 0 ; i < numbers_len ; i++)
    {
        free(st_numbers[i].num);
    }
    free(st_numbers);
    
    for(int i = 0 ; i < comb_num ; i++)
    {
        free(st_comb[i].num);
    }
    free(st_comb);

    return answer;
}

/**************************
 * define functions
 **************************/

// 팩토리얼 계산 함수
int factorial(int n) {
    if(n <= 1) return 1;
    return n * factorial(n - 1);
}

// 순열 생성 함수 (재귀적 방법)
void generate_permutations(st_node * numbers, int start, int end, st_node * combinations, int * comb_index) {
    if(start == end) {
        // 하나의 순열이 완성됨 - 문자열로 연결
        combinations[*comb_index].num[0] = '\0';  // 빈 문자열로 시작
        for(int i = 0; i <= end; i++) {
            strcat(combinations[*comb_index].num, numbers[i].num);
        }
        (*comb_index)++;
        return;
    }
    
    for(int i = start; i <= end; i++) {
        // 현재 위치와 i번째 위치 교환
        st_node temp = numbers[start];
        numbers[start] = numbers[i];
        numbers[i] = temp;
        
        // 재귀적으로 다음 위치의 순열 생성
        generate_permutations(numbers, start + 1, end, combinations, comb_index);
        
        // 원래대로 되돌리기 (백트래킹)
        temp = numbers[start];
        numbers[start] = numbers[i];
        numbers[i] = temp;
    }
}

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
        while(data_set[left].first_num <= pivot && left < right)
        {
            left++;
        }
        while(data_set[right].first_num >= pivot && left <= right)
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

