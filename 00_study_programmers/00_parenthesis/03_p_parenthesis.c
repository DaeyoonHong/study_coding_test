#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool solution(const char *s)
{
    int p_left = 0;
    int error = 0;
    int index = 0;

    while (s[index] != '\0')
    {
        if (s[index] == '(')
        {
            p_left++;
        }
        else if (s[index] == ')')
        {
            if (p_left == 0)
            {
                return false;
            }
            else
            {
                p_left--;
            }
        }
        index++;
    }

    if(p_left == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* CA */