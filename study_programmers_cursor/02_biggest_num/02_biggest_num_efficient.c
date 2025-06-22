/**************************
 * 입력 : 배열
 * 출력 : 문자열
 * 연산 : 문자열 비교 기반 정렬
 **************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 두 문자열을 연결했을 때 어떤 것이 더 큰지 비교하는 함수
int compare_strings(const void* a, const void* b) {
    char str1[20], str2[20];
    
    // a + b 형태로 연결
    sprintf(str1, "%s%s", *(char**)a, *(char**)b);
    // b + a 형태로 연결
    sprintf(str2, "%s%s", *(char**)b, *(char**)a);
    
    // 사전순 비교 (내림차순)
    return strcmp(str2, str1);
}

char* solution(int numbers[], size_t numbers_len) {
    // 문자열 배열 생성
    char** str_numbers = (char**)malloc(sizeof(char*) * numbers_len);
    
    // 각 숫자를 문자열로 변환
    for(int i = 0; i < numbers_len; i++) {
        str_numbers[i] = (char*)malloc(sizeof(char) * 5);
        sprintf(str_numbers[i], "%d", numbers[i]);
    }
    
    // 문자열 비교 함수로 정렬
    qsort(str_numbers, numbers_len, sizeof(char*), compare_strings);
    
    // 정렬된 문자열들을 연결
    char* answer = (char*)malloc(sizeof(char) * (numbers_len * 4 + 1));
    answer[0] = '\0';
    
    for(int i = 0; i < numbers_len; i++) {
        strcat(answer, str_numbers[i]);
    }
    
    // 모든 숫자가 0인 경우 처리
    if(answer[0] == '0') {
        answer[1] = '\0';
    }
    
    // 메모리 해제
    for(int i = 0; i < numbers_len; i++) {
        free(str_numbers[i]);
    }
    free(str_numbers);
    
    return answer;
}
/*
int main(void) 
{
    int numbers[] = {6, 10, 2};
    char* ans = solution(numbers, 3);
    
    printf("가장 큰 수: %s\n", ans);
    
    free(ans);
    return 0;
} 
*/