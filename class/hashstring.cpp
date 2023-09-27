// #include <stdio.h>
// #include <cstdlib>
// #include <cstring>
// #include <vector>

// #define M 1000000009
// #define P 31

// unsigned long my_pow(int base, int power)
// {
//     unsigned long res = 1;
//     for (int i = 0; i < power; i++)
//     {
//         res *= base;
//     }
//     return res;
// }

// unsigned long hash(char *str)
// {
//     unsigned long value = 0;
//     for (int i = 0; i < strlen(str); i++)
//     {
//         //ASCII
//         //value += (str[i] * my_pow(P, i)) % M;
//         //A = 1
//         value += ((str[i] - 96) * my_pow(P, i)) % M;
//     }
//     return (value % M);
// }

// int main(int argc, char **argv)
// {
//     if (argc != 3)
//     {
//         printf("Usage: %s <string1> <string2>\n", argv[0]);
//         return 1;
//     }
//     char *str1 = argv[1];
//     char *str2 = argv[2];

//     printf("The values are %lu and %lu\n", hash(str1), hash(str2));

//     return 0;
// }

#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <vector>

#define M 1000000009
#define P 31

unsigned long my_pow(unsigned long base, unsigned long power) // Use unsigned long to prevent overflow
                                                            // unasigned long helps us handling large numbers
{
    unsigned long res = 1;
    base %= M; // Module at each step to prevent overflow
    while (power) //
    {
        if (power & 1)
            res = (res * base) % M;
        base = (base * base) % M;
        power >>= 1;
    }
    return res;
}

unsigned long hash(const char *str) // const char *str is a pointer to a constant character
                                    // This means that the value of the character cannot be changed
{
    unsigned long value = 0;
    unsigned long len = strlen(str); // stores strlen(str) in len so that strlen is not called at every iteration
    for (unsigned long i = 0; i < len; i++)
    {
        unsigned long char_val = str[i] - 'a' + 1; // Ensure 'a' maps to 1
        value = (value + (char_val * my_pow(P, i)) % M) % M; // Ensure module operation is applied at every step
    }
    return value;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: %s <string1> <string2>\n", argv[0]);
        return 1;
    }

    printf("The values are %lu and %lu\n", hash(argv[1]), hash(argv[2]));

    return 0;
}