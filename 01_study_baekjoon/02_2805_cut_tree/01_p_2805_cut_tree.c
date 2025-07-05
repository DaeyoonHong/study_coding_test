#include <stdio.h>
#include <stdlib.h>

long long binary_search(long long *tree, long long tree_num, long long target)
{
    long long left, right, mid;
    left = 1;
    right = tree[tree_num - 1];

    long long temp_ans = 0;
    while(left <= right)
    {
        mid = (left + right) / 2;
        long long cut_result = cut_tree(tree, tree_num, mid);

        if(cut_result == target)
        {
            return mid;
        }
        else if(cut_result > target)
        {
            temp_ans = mid;
            left = mid + 1;
            mid = (left + right)/2;
        }
        else if(cut_result < target)
        {
            right = mid - 1;
            mid = (left + right) / 2;
        }
    }
    return temp_ans;
}

int compare(const void *elem1, const void *elem2)
{
    long long tree1 = *(long long *)elem1;
    long long tree2 = *(long long *)elem2;

    if(tree1 > tree2)
    {
        return 1;
    }
    else if(tree1 < tree2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

long long cut_tree(long long *tree, long long tree_num, long long height)
{
    long long result;
    for(long long i = 0; i < tree_num; i++)
    {
        if(tree[i] > height) /* result 연산에 음수가 섞이지 않도록 조치 */
        {
            result += tree[i] - height;
        }
    }

    return result;
}
