#include "main.hpp"
#include <vector>
#include <string>

// Ahora la función devuelve una LCSResult en lugar de un std::pair
LCS_Result longest_common_substring(const std::string& s1, const std::string& s2) {
    int n1 = s1.size(), n2 = s2.size();
    std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2 + 1));
    int max_length = 0, end_index_s1 = 0;

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_length) {
                    max_length = dp[i][j];
                    end_index_s1 = i;
                }
            }
        }
    }

    // Crea una instancia de LCSResult con los resultados y la devuelve
    LCS_Result result;
    result.length = max_length;
    result.start_index = end_index_s1 - max_length;
    result.end_index = end_index_s1 - 1;
    
    return result;
}

