/**************************
 * 연산 : 
 * 두 문자열을 연결했을 때 어떤 문자를 앞에 두어야 더 큰지 비교하는 compare 함수와
 * 이를 사용하는 qsort(라이브러리 함수) 를 이용해 문자열을 정렬
 **************************/

 /************************
  * include libraries
  ************************/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 /***********************
  * functions prototypes
  ***********************/
int compare_strings(const void * a, const void * b)
/* compare_strings 의 입력인자는 배열 요소들의 주소 - &str_numbers[0] */
{
   char str1[9];
   char str2[9];

   /*
   sprintf 는 문자열을 생성하는 함수
   ex) 
   char* result = (char*)malloc(100 * sizeof(char));
   sprintf(result, "%s%d%s", "Number: ", 42, " is the answer");
   */

   sprintf(str1, "%s%s", *(char**)a, *(char**)b);
   sprintf(str2, "%s%s", *(char**)b, *(char**)a);

   /* 
   아래와 같은 형태의 문자열 배열을 가리키는 포인터 나타내기 위해 이중 포인터를 사용
   [[a, b, c], [d, e, f]...]
   - a: 문자열 포인터 배열을 가리키는 포인터
   - a[i]: 개별 문자열을 가리키는 포인터
   - a[i][j]: 개별 문자
   */

   return strcmp(str2, str1); 
   /* compare 함수의 출력이 음수이면 순서 유지, 양수이면 순서 변경 */
   /* 
   strcmp 함수 출력
   - 음수 : 입략된 두 요소가 사전 순 
   - 양수 : 입력된 두 요소가 사전 순 반대
   - 0 : 같음
   */
}

char * solution(int numbers[], size_t numbers_len)
{
    char ** str_numbers = (char **)malloc(sizeof(char *) * numbers_len);
    for(int i = 0 ; i < numbers_len ; i++)
    {
        str_numbers[i] = (char *)malloc(sizeof(char) * 5);
        sprintf(str_numbers[i], "%d", numbers[i]);
        /* %d 형 데이터 (numbers[i]) 를 문자열로 변경하여 str_numbers[i] 에 저장 */
        /* 문자열을 저장하고자 하는 버퍼(str_numbers[i]) 에 충분한 저장공간을 미리 확보해 두어야 함*/
    }

    qsort(str_numbers, numbers_len, sizeof(char *), compare_strings);
    
    char * answer = (char *)malloc(sizeof(char) * numbers_len * 4 + 1);
    answer[0] = ' \0';

    for(int i = 0 ; i < numbers_len ; i++)
    {
        strcat(answer, str_numbers[i]);
    }

    if(answer[0] == '0')
    {
        answer[1] == '\0';
    }

    for(int i = 0; i < numbers_len ; i++)
    {
        free(str_numbers[i]);
    }
    free(str_numbers);

    return answer;
}