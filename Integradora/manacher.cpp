#include "main.hpp"

//Find the biggest palindrome in pattern
static int *manacher_inner(char *pattern, int *biggest)
{
    int *l = (int *)malloc(sizeof(int) * strlen(pattern));
    l[0] = 0;
    l[1] = 1;
    int i = 1, count = 0;
    for (int k = 2; k < strlen(pattern); k++)
    {
        while((k - i) >= 0 && (k + i) < strlen(pattern) && pattern[k - i] == pattern[k + i])
        {
            i++;
            count++;
            if (count > *biggest)
                *biggest = count;
        }
        l[k] = count;
        count = 0;
        i = 1;
    }
    return l;
}

int manacher(const char *main, int *biggest)
{
    char *new_string = (char *)malloc(sizeof(char) * ((strlen(main) * 2) + 1));

    new_string[0] = '$';
    for (int i = 0; i < strlen(main); i++)
    {
        new_string[(i * 2) + 1] = main[i];
        new_string[(i * 2) + 2] = '$';
    }
    //printf("%s\n", new_string);

    int *l = manacher_inner(new_string, biggest);
    int position;

    for (int i = 0; i < strlen(new_string); i++)
    {
        //printf("%d ", l[i]);
        if (l[i] == *biggest)
        {
            position = (i - *biggest) / 2;
            free(l);
            free(new_string);
            return(position);
        }
    }

    free(l);
    free(new_string);
    return -1;
}