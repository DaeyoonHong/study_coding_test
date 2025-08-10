/*****************************
 * include libraries
 *****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************
 * define datatypes
 *****************************/

/*****************************
 * function prototypes
 *****************************/
int max(int v1, int v2);


/*****************************
 * main function
 *****************************/
int main(void)
{
    int remain_days;
    
    scanf("%d", &remain_days);
    
    int *req_days = (int *)malloc(sizeof(int) * (remain_days + 1));
    int *income = (int *)malloc(sizeof(int) * (remain_days + 1));
    
    for (int i = 1; i < remain_days + 1; i++)
    {
        scanf("%d %d", &req_days[i], &income[i]);
    }
    
    int **dp = (int **)malloc(sizeof(int *) * (2));
    
    for (int i = 0; i < 2 + 1; i++)
    {
        dp[i] = (int *)malloc(sizeof(int) * (remain_days + 1));
    }
    
    for (int i = 0; i < remain_days + 1; i++)
    {
        dp[0][i] = 0;
    }
    
    for (int i = 1; i < remain_days + 1; i++)
    {
        for (int j = 1; j < remain_days + 1; j++) 
        /* dp[i][j] : i번째 물건 까지 고려한 경우 j일 만큼 사용했을 때 최대 가치 */
        {
            if (j - (i - 1) >= req_days[i])
            {
                dp[1][j] = max(dp[0][j], dp[0][i - req_days[i]] + income[i]);
            }
            else
            {
                dp[1][j] = dp[0][j];
            }
        }
        memcpy(dp[0], dp[1], sizeof(int) * (remain_days + 1));
    }
    
    printf("%d", dp[1][remain_days]);
    
    free(req_days);
    free(income);
    for (int i = 0; i < 2; i++)
    {
        free(dp[i]);
    }
    free(dp);
    
    return 0;
}

/*****************************
 * define functions
 *****************************/
int max(int v1, int v2)
{
    int ret;
    
    if (v1 >= v2)
    {
        ret = v1;
    }
    else
    {
        ret = v2;
    }
    
    return ret;
}