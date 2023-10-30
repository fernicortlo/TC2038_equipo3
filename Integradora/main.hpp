#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>

int z_function(const char *main, const char *pattern);
int manacher(const char *main, int *biggest);

struct LCS_Result {
    int length;      // Length of the longest common substring
    int start_index; // Starting index of the LCS in the first string
    int end_index;   // Ending index of the LCS in the first string
};
LCS_Result longest_common_substring(const std::string& s1, const std::string& s2);

