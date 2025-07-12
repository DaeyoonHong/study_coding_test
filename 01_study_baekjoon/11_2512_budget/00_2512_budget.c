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
    int n;
    int budget;

    scanf("%d", &n);

    int *req = (int *)malloc(sizeof(int) * n);
    int req_max = 0;
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &req[i]);
        if(req_max < req[i])
        {
            req_max = req[i];
        }
    }
    scanf("%d", &budget);

    int left = 1;
    int right = req_max;
    int mid = 0;
    int temp = 0;
    int max = 0;

    while(left <= right)
    {
        mid = (left + right) / 2;
        temp = 0;
        for(int i = 0; i < n; i++)
        {
            if(mid - req[i] >= 0)
            {
                temp = temp + req[i];
            }
            else
            {
                temp = temp + mid;
            }
        }
        
        if(temp == budget)
        {
            max = mid;
            break;
        }
        else if(temp > budget)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
            max = mid;
        }
    }   

    printf("%d", max);

    free(req);
    return 0;
}

/*****************************
 * define functions
 *****************************/