//** Header que contiene la declaracion de nuestras funciones

using namespace std;
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>


//** Funciones primera parte

string lectura_txt(string archivo);
vector<int> prefix_function(string &pattern);
int kmp_function(string &transmission, string &pattern, vector<int> &prefix);

//** Funciones segunda parte

int manacher(const char *main, int *biggest);

//** Funciones tercera parte

struct LCS_Result {
    int length;      // Length of the longest common substring
    int start_index; // Starting index of the LCS in the first string
    int end_index;   // Ending index of the LCS in the first string
};
LCS_Result longest_common_substring(const std::string& s1, const std::string& s2);