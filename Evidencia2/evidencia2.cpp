/* 
    Evidencia 2. Actividad Integradora 2
    Equipo 3. 
        - Maria Fernanda Cortés Lozano | A01026613
        - Mario Frias Piña | A0
        - Juan Pablo Cruz | A0
    
    Este programa  resuelve tres problemas relacionados con la planificación de servicios de Internet y logística en una ciudad.
    En primer lugar, determina la forma óptima de conectar colonias con fibra óptica de manera que se pueda compartir información 
    entre todas las colonias, utilizando el algoritmo de Kruskal para encontrar un árbol de expansión mínima en un grafo ponderado. 
    En segundo lugar, encuentra la ruta más corta que visita cada colonia exactamente una vez y regresa a la colonia de origen, 
    conocido como el Problema del Viajante de Comercio (TSP), y muestra esta ruta. 
    Finalmente, calcula la distancia al servidor más cercano desde varios puntos de la ciudad, basándose en la ubicación de 
    las centrales, para ayudar a decidir cuál es la central más cercana geográficamente para una nueva contratación del 
    servicio de Internet.
*/

#include "evidencia2.hpp"
#include <iostream>
#include <algorithm> // to use sort
#include <fstream> // to read the file

/* 
Traveling Salesman Problem: 
*/
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

void find_path(int node, int length, int currentCost, int &min, const std::vector<std::vector<int>>& matrix, int *path, std::vector<bool> &visited, std::vector<int> &tspPath)
{
    int size = visited.size();
    if (length == size)
    {
        if (currentCost + matrix[node][path[0]] < min)
        {
            min = currentCost + matrix[node][path[0]];

            // Store the path
            for (int i = 0; i < size; i++)
            {
                tspPath[i] = path[i];
            }
            return; // Correctly terminate the recursion here
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (!visited[i] && matrix[node][i] != INT_MAX &&
            currentCost + matrix[node][i] < min)
        {
            visited[i] = true;
            path[length] = i;

            find_path(i, length + 1, currentCost + matrix[node][i], min, matrix, path, visited, tspPath);

            visited[i] = false;
        }
    }
}

int tsp_solve(int size, const std::vector<std::vector<int>>& matrix, std::vector<int>& tspPath)
{
    int path[size + 1];
    std::vector<bool> visited(size, false);
    int minimum = INT_MAX;

    // Add the origin to the path and visited nodes
    visited[0] = true;

    path[0] = 0;
    path[size] = 0;
    find_path(0, 1, 0, minimum, matrix, path, visited, tspPath);

    printf("\nCost: %d\n", minimum);
    return minimum; // Return the minimum cost
}

/*
MST: Kruskal's Algorithm
*/
int findParent(int vertex, std::vector<int>& parent) {
    if (vertex == parent[vertex])
        return vertex;
    return parent[vertex] = findParent(parent[vertex], parent);
}

void kruskal(const std::vector<Edge>& edges, int n, std::vector<Edge>& mst) {
    std::vector<int> parent(n);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Sort edges by their weight
    std::vector<Edge> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    int count = 0; // Number of edges added to MST
    for (const auto& edge : sortedEdges) {
        int sourceParent = findParent(edge.source, parent);
        int destinationParent = findParent(edge.dest, parent);

        // If adding this edge doesn't form a cycle
        if (sourceParent != destinationParent) {
            mst.push_back(edge);  // Add the edge to the MST
            parent[sourceParent] = destinationParent;
            count++;
            if (count == n - 1) break; // MST is complete when it has n-1 edges
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s %s\n", argv[0], argv[1]);
        return 1;
    }

    int size = 0;

    std::ifstream file(argv[1]);
    std::vector<Point>  points;
    std::vector<std::vector<int>> matrix;
    std::vector<int> tspPath;
    
    if (file.is_open()) {
        std::string line;
        int count = 0;
        
        //Read Size of matrix
        file >> size;
        matrix.resize(size, std::vector<int>(size)); // Resize the matrix

        // Read the matrix from the file
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (!(file >> matrix[i][j])) {
                    std::cout << "Error reading matrix from file\n";
                    return 1;
                }
            }
        }

        // Convert matrix to edges for Kruskal
        std::vector<Edge> edges;
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if (matrix[i][j] != 0 && matrix[i][j] != INT_MAX) { // Assuming 0 or INT_MAX means no direct connection
                    edges.push_back({i, j, matrix[i][j]});
                }
            }
        }

        //Read Points
        Point p;
        while (file >> p.x >> p.y)
            points.push_back(p);
        file.close();

        // Calculate nearest server distance for each point
        std::vector<double> nearestServerDistances;
        for (const Point& point : points) {
            double distance = findNearestServerDistance(point, points);
            nearestServerDistances.push_back(distance);
        }

        //Kruskal Solver
        std::vector<Edge> mst;
        kruskal(edges, size, mst);

        // Print cable plan for connecting colonies (list of edges)
        std::cout << "1. Forma de cablear las colonias con fibra (lista de arcos de la forma (A, B)):\n";
        for (const Edge &edge : mst)
        {
            char colonyA = 'A' + edge.source;
            char colonyB = 'A' + edge.dest;
            std::cout << "(" << colonyA << ", " << colonyB << ") ";
        }
        std::cout << "\n\n";

        //TSP Solver
        tspPath.resize(size); // Define tspPath here
        int tspCost = tsp_solve(size, matrix, tspPath);

        // Print the TSP path
        std::cout << "2. Ruta a seguir por el personal que reparte correspondencia:\n";
        for (size_t i = 0; i < tspPath.size(); ++i) {
            char colonyName = 'A' + tspPath[i];
            std::cout << colonyName << (i < tspPath.size() - 1 ? " -> " : " -> ") << colonyName;
        }
        std::cout << "\n\n";

        //Print nearest server distances
        for (size_t i = 0; i < nearestServerDistances.size(); ++i) {
            std::cout << "3. Servidor más cercano al punto " << i << ": " << nearestServerDistances[i] << std::endl;
        }
    }
    else {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    return 0;
}