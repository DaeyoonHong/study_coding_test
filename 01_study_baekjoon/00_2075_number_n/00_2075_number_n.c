/************************
 * 단순히 입력을 정렬하는 풀이 방법은 메모리를 초과함
 ************************/


/************************
 * include libraries
 ************************/
#include <stdio.h>
#include <stdlib.h>

/************************
 * function prototypes
 ************************/
int compare(const void * a, const void * b);

/************************
 * main function
 ************************/
int main(void)
{
    int n = 0;
    scanf("%d", &n);

    long * numbers = (long *)malloc(sizeof(long) * n * n);
    for(int i = 0 ; i < (n * n) ; i++)
    {
        scanf("%ld", &numbers[i]);
    }
    #if 0
    for(int i = 0; i < (n * n) ; i++)
    {
        printf("%d\n", numbers[i]);
    }
    #endif

    qsort(numbers, (n * n), sizeof(int), compare);

    #if 0
    for(int i = 0; i < (n * n) ; i++)
    {
        printf("%d", numbers[i]);
    }
    #endif


    printf("%ld", numbers[n - 1]);

    free(numbers);

    return 0;
}

/*************************
 * define functions
 *************************/
int compare(const void * a, const void * b)
{
    long num1 = *(long *) a;
    long num2 = *(long *) b;

    if(num1 > num2)
    {
        return -1;
    }
    else if(num1 < num2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
