/****************************
 * inclue libraties
 ****************************/
#include <stdio.h>
#include <stdlib.h>

/****************************
 * function prototypes
 ****************************/
long long binary_search(long long * tree, long long tree_num, long long target);
long long cut_tree(long long * tree, long long tree_num, long long height);
int compare(const void * element1, const void * element2);

/****************************~
 * main function
 ****************************/
int main(void)
{
    long long tree_num = 0;
    long long target = 0;
    long long ans = 0;

    scanf("%lld", &tree_num);
    scanf("%lld", &target);
    
    long long * tree = (long long *)malloc(sizeof(long long) * tree_num);
    
    for(int i = 0; i < tree_num ; i++)
    {
        scanf("%lld", &tree[i]);
    }

    qsort(tree, tree_num, sizeof(long long), compare);

    ans = binary_search(tree, tree_num, target);

    printf("%lld", ans);
    free(tree);

    return 0;
}



/****************************
 * define functions
 ****************************/
long long binary_search(long long * tree, long long tree_num, long long target)
{
    long long left, right, mid;
    left = 1;
    right = tree[tree_num - 1];
    
    /* 탐색 범위의 크기가 0 이 될 때까지 while 문을 반복 */
    long long temp_ans = 0;
    while(left <= right)
    {
        mid = (left + right) / 2;
        long long cut_result = cut_tree(tree, tree_num, mid);
        if(target == cut_result)
        {
            return mid;
        }
        else if(target > cut_result)
        {
            right = mid - 1;
            mid = (left + right) / 2;

        }
        else if(target < cut_result)
        {
            temp_ans = mid;     /* 나무가 모자라서는 안된다 */
            left = mid + 1;
            mid = (left + right) / 2;
        }
        else
        {
            /* nothing */
        }
    }
    return temp_ans;
}

long long cut_tree(long long * tree, long long tree_num, long long height)
{
    long long result = 0;
    for(long long i = 0; i < tree_num ; i++)
    {
        if(tree[i] > height)
        {
            result += tree[i] - height;
        }
    }

    return result;
}

int compare(const void * element1, const void * element2)
{
    long long elem1 = *(long long *)element1;
    long long elem2 = *(long long *)element2;

    if(elem1 < elem2)
    {
        return -1;
    }
    else if(elem1 > elem2)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}