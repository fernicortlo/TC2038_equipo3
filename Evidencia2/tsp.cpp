#include <vector>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <climits>

//Lower bound
int minCost(int current_node, std::vector<int> matrix, std::vector<bool> visited)
{
    int bound = 0;
    int size = visited.size();

    //Calculates the smallest possible value for each node left ignoring the zeros
    for (int i = 0; i < size; i++) {
        //Remove current and visited nodes
        if (i != current_node && !visited[i]) {
            int min = INT_MAX;
            for (int j = 0; j < size; j++) {
                //Ignore zeros
                if (matrix[i + (j * size)] != 0 && matrix[i + (j * size)] < min)
                    min = matrix[i + (j * size)];
            }
            //Add the non-zero value to our minimum
            bound += min;
        }
    }
    return bound;
}

void find_path(int node, int length, int currentCost, int &min, std::vector<int> matrix, int *path, std::vector<bool> &visited)
{
    int size = visited.size(); 
    if (length == size)
    {
        if (currentCost + matrix[node] < min)
        {
            min = currentCost + matrix[node];
            
            //Print path before it is modified
            printf("Path: ");
            for (int i = 0; i <= size; i++)
            {
                printf("%c ", 'A' + path[i]);
            }
        }
        return;
    }

    for (int i = 0; i < size; i++)
    {
        if (!visited[i] && matrix[node + (i * size)] != INT_MAX &&
            currentCost + matrix[node + (i * size)] + minCost(node, matrix, visited) < min)
        {
            visited[i] = true;
            path[length] = i;

            find_path(i, length + 1, currentCost + matrix[node + (i * size)], min, matrix, path, visited);

            visited[i] = false;
        }
    }
}

int tsp_solve(int size, std::vector<int> matrix)
{
    int path[size + 1];
    std::vector<bool> visited(size, false);
    int minimum = INT_MAX;

    //Add the origin to the path and visited nodes
    visited[0] = true;

    path[0] = 0;
    path[size] = 0;
    find_path(0, 1, 0, minimum, matrix, path, visited);

    printf("\nCost: %d\n", minimum);
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s %s\n", argv[0], argv[1]);
        return 1;
    }
    std::ifstream file(argv[1]);

    std::vector<int> matrix;
    int size = 0;

    //Read matrix from file
    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line)) {
            std::stringstream linestream(line);
            int num;
            int row_size = 0;

            while (linestream >> num) {
                if (num >= 0)
                    matrix.push_back(num);
                else
                    matrix.push_back(INT_MAX);
                row_size++;
            }
            size = row_size;
        }
        file.close();
    }

    //Print adjacency matrix
    for (int i = 0; i < size * size; i++)
    {
        printf("%d\t", matrix[i]);
        if (i % size == size - 1)
            printf("\n");
    }

    tsp_solve(size, matrix);
    return 0;
}