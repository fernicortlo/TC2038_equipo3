#include <stdio.h>
#include <cstdlib>
#include <cstring>

int     *prefix_function(char *pattern)
{
    int x = 0, y = 1;
    int *fun = (int *)malloc(sizeof(int) * strlen(pattern));
    fun[0] = 0;

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
            fun[y] = 0;
            x = 0;
        }
        y++;
    }
    return(fun);
}

int    find_substring(char *main, char *pattern, int *match)
{
    int i, j = 0;

    for (i=0; i < strlen(main); i++)
    {
        //printf("%c %c\n", main[i], pattern[j]);
        if (pattern[j] == main[i])
        {
            j++;
        }
        else
        {
            //printf("Go to: %c in position %d\n", pattern[match[j -1]], match[j-1]);
            j = match[j+1];
        }
        if (pattern[j] == '\0')
        {
            return (i + 1 - strlen(pattern));
        }
    }
    return -1;
}

int     main(int argc, char **argv)
{
    char *pattern = argv[1];

    int *fun = prefix_function(pattern);

    for (int i = 0; i < strlen(pattern); i++)
        printf("%d ", fun[i]);

    printf("\n");

    int substring_position = find_substring(argv[2], pattern, fun);
    printf("Found the pattern '%s' in the main string '%s' starts in position %d '%s'\n", argv[1], argv[2], substring_position, &argv[2][substring_position]);
    free(fun);
    return 0;
}
