/**************************
 * 입력 : 배열
 * 출력 : 문자열
 * 연산 : 첫 번째 자릿수 기반 정렬
 **************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* num;
    char first_digit;
    int original_index;
} NumberInfo;

// 첫 번째 자릿수로 내림차순 정렬
int compare_by_first_digit(const void* a, const void* b) {
    NumberInfo* num1 = (NumberInfo*)a;
    NumberInfo* num2 = (NumberInfo*)b;
    
    // 첫 번째 자릿수가 다르면 내림차순
    if(num1->first_digit != num2->first_digit) {
        return num2->first_digit - num1->first_digit;
    }
    
    // 첫 번째 자릿수가 같으면 전체 숫자 비교
    return strcmp(num2->num, num1->num);
}

char* solution(int numbers[], size_t numbers_len) {
    NumberInfo* num_info = (NumberInfo*)malloc(sizeof(NumberInfo) * numbers_len);
    
    // 각 숫자 정보 초기화
    for(int i = 0; i < numbers_len; i++) {
        num_info[i].num = (char*)malloc(sizeof(char) * 5);
        sprintf(num_info[i].num, "%d", numbers[i]);
        num_info[i].first_digit = num_info[i].num[0];
        num_info[i].original_index = i;
    }
    
    // 첫 번째 자릿수 기준으로 정렬
    qsort(num_info, numbers_len, sizeof(NumberInfo), compare_by_first_digit);
    
    // 정렬된 순서로 문자열 연결
    char* answer = (char*)malloc(sizeof(char) * (numbers_len * 4 + 1));
    answer[0] = '\0';
    
    for(int i = 0; i < numbers_len; i++) {
        strcat(answer, num_info[i].num);
    }
    
    // 모든 숫자가 0인 경우 처리
    if(answer[0] == '0') {
        answer[1] = '\0';
    }
    
    // 메모리 해제
    for(int i = 0; i < numbers_len; i++) {
        free(num_info[i].num);
    }
    free(num_info);
    
    return answer;
}

int main(void) {
    int numbers[] = {6, 10, 2};
    char* ans = solution(numbers, 3);
    
    printf("가장 큰 수: %s\n", ans);
    
    free(ans);
    return 0;
} 