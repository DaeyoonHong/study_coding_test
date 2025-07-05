/**************************
 * include libraries
 **************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**************************
 * define datatypes
 **************************/

/************************* 
 * function prototypes
**************************/
void word_cmp(const char * word1, char * word2, char * a, int depth, int len);

/************************* 
 * main function
**************************/
int answer = 0;

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* word) 
{
    int len = strlen(word);
    char a[5] =  {'A', 'E', 'I', 'O', 'U'};


    char * current_word = (char *)malloc(sizeof(char) * len+ 1);
    word_cmp(word, current_word, a, 1, len);
    
    printf("%d", answer + 1);

    return 0;
}

int main(void)
{
    const char word[2] = {'I', '\0'};

    solution(word);

    return 0;
}

/******************************
 * define functions
 ******************************/
void word_cmp(const char * word1, char * word2, char * a, int depth, int len)
{
    for(int i = 0 ; i < 5 ; i++)
    {
        word2[depth - 1] = a[i];
        word2[depth] = '\0';

        int compare = 0;
        compare = strcmp(word1, word2);
        if(compare > 0)
        {
            answer++;
        }
        if(depth < 5)
        {
            word_cmp(word1, word2, a, depth + 1, len);
        }
    }
}
