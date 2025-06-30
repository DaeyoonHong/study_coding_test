#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b)
{
    char str1[9];
    char str2[9];

    sprintf(str1, "%s%s", *(char **)a, *(char **)b);
    sprintf(str2, "%s%s", *(char **)b, *(char **)a);

    return strcmp(str2, str1);
}

char *solution(int numbers[], size_t numbers_len)
{
    char **str_numbers = (char **)malloc(sizeof(char *) * numbers_len);
    for (int i = 0; i < numbers_len; i++)
    {
        str_numbers[i] = (char *)malloc(sizeof(char) * 5);
        sprintf(str_numbers[i], "%d", numbers[i]);
    }

    qsort(str_numbers, numbers_len, sizeof(char *), compare_strings);

    char *answer = (char *)malloc(sizeof(char) * numbers_len * 4 + 1);
    answer[0] = '\0';

    for(int i = 0; i < numbers_len; i++)
    {
        strcat(answer, str_numbers[i]);
    }

    if(answer[0] = '0')
    {
        answer[1] = '\0';
    }

    for(int i = 0; i < numbers_len; i++)
    {
        free(str_numbers[i]);
    }
    free(str_numbers);

    return answer;
}