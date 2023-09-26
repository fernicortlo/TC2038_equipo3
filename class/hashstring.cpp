#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <vector>

#define M 1000000009
#define P 31

unsigned long my_pow(int base, int power)
{
    unsigned long res = 1;
    for (int i = 0; i < power; i++)
    {
        res *= base;
    }
    return res;
}

unsigned long hash(char *str)
{
    unsigned long value = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        //ASCII
        value += (str[i] * my_pow(P, i)) % M;
        //A = 1
        //value += (str[i] * my_pow(P, i)) % M;
    }
    return (value % M);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }
    char *str1 = argv[1];
    char *str2 = argv[2];

    printf("The values are %lu and %lu\n", hash(str1), hash(str2));

    return 0;
}