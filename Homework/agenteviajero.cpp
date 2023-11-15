#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

// Function to find the minimum edge cost having an end at the vertex i
int findMinEdgeCost(int i, const vector<vector<int> >& adjMatrix, const vector<bool>& visited) {
    int minCost = INT_MAX;
    int n = adjMatrix.size();
    for (int j = 0; j < n; ++j) {
        if (!visited[j] && adjMatrix[i][j] < minCost && adjMatrix[i][j] > 0) {
            minCost = adjMatrix[i][j];
        }
    }
    return (minCost == INT_MAX) ? 0 : minCost;
}

// Recursive function to implement the traveling salesman problem
void tsp(int current, vector<bool>& visited, int n, int count, int cost, int& ans, const vector<vector<int> >& adjMatrix) {
    if (count == n && adjMatrix[current][0]) {
        ans = min(ans, cost + adjMatrix[current][0]);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && adjMatrix[current][i]) {
            visited[i] = true;
            tsp(i, visited, n, count + 1, cost + adjMatrix[current][i], ans, adjMatrix);
            visited[i] = false;
        }
    }
}

// Function to start the TSP algorithm
int TSP(const vector<vector<int> >& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    visited[0] = true;
    int ans = INT_MAX;

    tsp(0, visited, n, 1, 0, ans, adjMatrix);

    return ans;
}

// Main Function
int main() {
    ifstream inputFile("tsp_matrix.txt");
    string line;
    vector<vector<int> > adjMatrix;
    int num;

    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<int> row;
        while (ss >> num) {
            if (num < 0) num = INT_MAX;
            row.push_back(num);
        }
        adjMatrix.push_back(row);
    }
    inputFile.close();

    int result = TSP(adjMatrix);

    cout << "Minimum Cost: " << result << endl;

    return 0;
}
