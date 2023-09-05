#include <stdio.h>
#include <cstdlib>
#include <cstring>

int *prefix_function(char *pattern)
{
    int x = 0, y = 1;
    int *fun = (int *)malloc(sizeof(int) * strlen(pattern));
    fun[0] = -1;

    while (pattern[y] != '\0')
    {
        //printf("Comparing %c and %c\n", pattern[y], pattern[x]);
        if (pattern[y] == pattern[x])
        {
            fun[y] = x;
            x++;
        }
        else if (pattern[y] == pattern[0])
        {
            fun[y] = 0;
            x = 1;
        }
        else
        {
            fun[y] = -1;
            x = 0;
        }
        y++;
    }
    return(fun);
}

int main(int argc, char **argv)
{
    char *pattern = argv[1];

    int *fun = prefix_function(pattern);

    for (int i = 0; i < strlen(pattern); i++)
        printf("%d ", fun[i]);

    printf("\n");
    free(fun);
    return 0;
}
