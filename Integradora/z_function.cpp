#include "main.hpp"

static int *z_function(const char *pattern)
{
    int *z = (int *)malloc(sizeof(int) * strlen(pattern));
    z[0] = 0;
    int i = 0, j = 1, count = 0;
    for (int k = 1; k < strlen(pattern); k++)
    {
        while(pattern[i] == pattern[j])
        {
            i++;
            j++;
            count++;
        }
        z[k] = count;
        count = 0;
        i = 0;
        j = k + 1;
    }
    return (z);
}

int z_function(const char *main, const char *pattern)
{
    char *final = (char *)malloc(sizeof(char) * (strlen(pattern) + strlen(main) + 1));

    strcpy(final, pattern);
    strcat(final, "$");
    strcat(final, main);

    //printf("%s\n", final);

    int *z = z_function(final);
    std::vector <int> found;
    for (int i = 0; i < strlen(final); i++)
    {
        if (z[i] == strlen(pattern))
            found.push_back(i - strlen(pattern) - 1);
        //printf("%d ", z[i]);
    }
    //printf("\n");
    free(z);
    free(final);

    for (int i: found)
    {
        return (i + 1);
        //printf("The pattern is found in position %d %s\n", i, &main[i]);
    }
    return -1;
}