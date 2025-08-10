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
    long long n, k;
    scanf("%lld", &n);
    scanf("%lld", &k);
   
    long long left = 1;
    long long right = n * n;
    long long mid;
    long long answer;

    while (left <= right)
    {
        mid = (left + right) / 2;
        
        long long num_of_mid = 0;
        
        for (long long i = 1; i <= n; i++)
        {
            if (mid / i > n)
            {
                num_of_mid = num_of_mid + n;
            }
            else
            {
                num_of_mid = num_of_mid + (mid / i);
            }
        }
        
        if(num_of_mid < k)
        {
            left = mid + 1;
        }
        else
        {
            answer = mid;
            right = mid - 1;
        } 
    }
    
    printf("%lld", answer);
    
    return 0;
}

/*****************************
 * define functions
 *****************************/