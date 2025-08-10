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
int max(int v1, int v2);

/*****************************
 * main function
 *****************************/
int main(void)
{
    int n, k;
    
    scanf("%d %d", &n, &k);
    
    int *w = (int *)malloc(sizeof(int) * n);
    int *v = (int *)malloc(sizeof(int) * n);
    
    
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &w[i], &v[i]);
    }
    
    int **dp = (int **)malloc(sizeof(int *) * n);
    
    for (int i = 0; i < n; i++)
    {
        dp[i] = (int *)malloc(sizeof(int) * (k + 1));
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k + 1; j++)
        {
            if (i != 0)
            {
                if (j - w[i] > 0)
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
            else
            {
                if (j - w[0] > 0)
                {
                    dp[0][j] = v[0];
                }
                else
                {
                    dp[0][j] = 0;
                }
            } 
        }
    }
    
    printf("%d", dp[n - 1][k]);
    
    free(w);
    free(v);
    for (int i = 0; i < n; i++)
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
