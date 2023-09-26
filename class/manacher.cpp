#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <vector>

int *manacher(char *pattern, int *biggest)
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

int main(int argc, char **argv)
{
    if (argc!= 2)
    {
        printf("Usage: %s <main>\n", argv[0]);
        return 1;
    }

    char *main = argv[1];
    char *new_string = (char *)malloc(sizeof(char) * ((strlen(main) * 2) + 1));
    int biggest = 0;

    new_string[0] = '$';
    for (int i = 0; i < strlen(main); i++)
    {
        new_string[(i * 2) + 1] = main[i];
        new_string[(i * 2) + 2] = '$';
    }
    printf("%s\n", new_string);

    int *l = manacher(new_string, &biggest);
    char *position;
    int done = 0;

    for (int i = 0; i < strlen(new_string); i++)
    {
        printf("%d ", l[i]);
        if (l[i] == biggest && !done)
        {
            //printf("\n%d %d\n", i, biggest);
            position = &main[(i - biggest) / 2];
            position[biggest] = '\0';
            done = 1;
        }
    }

    printf("\nThe biggest palindrome is %s of size %d\n", position, biggest);
    free(l);
    free(new_string);

    return 0;
}