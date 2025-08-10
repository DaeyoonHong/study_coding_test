/*****************************
 * include libraries
 *****************************/
#include <stdio.h>
#include <stdlib.h>

/*****************************
 * define datatypes
 *****************************/

/*****************************
 * function prototypes
 *****************************/

/*****************************
 * main function
 *****************************/
int main(void)
{
    int width;
    
    scanf("%d", &width);
    
    long long *dp = (long long *)malloc(sizeof(long long) * (width + 1));
    
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i < width + 1; i++)
    {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;
    }

    int ans = dp[width];

    printf("%d", ans);
    
    free(dp);
    
    return 0;
}

/*****************************
 * define functions
 *****************************/