// Created by Fer Cortés, Mario Frías, and Juan Pablo Cruz
// Date: 22/09/2023

// Kruskal algorithm implementation
// This algorithm is used to find the minimum spanning tree of a graph, it receives a .txt file with the graph information.
// The file must have the following format:
// 1 2 3 (node1 node2 weight)
// And the output will be:
// The used connections and their final weight
#include <vector>
#include <iostream>
#include <algorithm> // to use sort
#include <fstream> // to read the file
using namespace std;

// represents an edge in the graph
class Edge {
public:
    int source;
    int dest;
    int weight;
};

// Compares two edges by weight
bool compare(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

// recursive function to find the set of an element v
int findParent(int v, int *parent) {
    if (parent[v] == v) {
        return v;
    }
    return findParent(parent[v], parent);
}

// Main Kruskal's algorithm function
void kruskal(Edge* input, int n, int E) {
    // Sort input array in ascending order by weight
    sort(input, input + E, compare);

    // Output array, will store the final minimum spanning tree
    Edge *output = new Edge[n - 1]; // n-1 edges in the minimum spanning tree (n vertices) 

    // Array to keep track of sets of vertices to detect cycles
    int *parent = new int[n]; 
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int count = 0; // Keeps track of the number of edges added to the output array
    int i = 0; // Keeps track of the current edge being processed
    while (count != n - 1) {
        Edge currentEdge = input[i];

        // Check if currentEdge can be added to the output array
        int sourceParent = findParent(currentEdge.source, parent); // Find the set of the source vertex
        int destinationParent = findParent(currentEdge.dest, parent); // Find the set of the destination vertex

        // If the source and destination vertices are in different sets, add the currentEdge to the output array
        // checks if adding the currentEdge will create a cycle
        if (sourceParent != destinationParent) {
            output[count] = currentEdge;
            count++;
            parent[sourceParent] = destinationParent;
        }
        i++;
    }

    // Print the output array
    int totalWeight = 0;
    cout << "Conexiones usadas: " << endl;
    for (int i = 0; i < n-1; i++) {
        cout << "[" << output[i].source << "," << output[i].dest << "," << output[i].weight << "] " << endl;
        totalWeight += output[i].weight;
    }
    cout << "Peso final: " << totalWeight << endl;

    // deletes memory allocated for the arrays
    delete[] output;
    delete[] parent;
}

int main() {
    //opens the file
    ifstream file("input.txt");
    
    if(!file.is_open()) {
        cout << "¡Error al abrir el archivo!" << endl;
        return 0;
    }

    // Vector to store all the edges from the file
    vector<Edge> inputEdges;
    // Track the maximum vertex number
    int maxVertex = -1;  // Initialize with -1 to ensure at least vertex 0 is counted

    // Read the file and store the edges in the vector
    while(!file.eof()) {
        Edge currentEdge;
        file >> currentEdge.source >> currentEdge.dest >> currentEdge.weight;
        
        // Update the maximum vertex number
        maxVertex = max(maxVertex, max(currentEdge.source, currentEdge.dest));  // Update the maximum vertex number
        
        // Add the current edge to the vector
        inputEdges.push_back(currentEdge); //push_back adds the element to the end of the vector, increasing its size by 1
        // method of vector 
    }

    int n = maxVertex + 1;  // Total vertices is maximum vertex number + 1
    int E = inputEdges.size();  // Total number of edges

    // Create an array of edges to pass to the kruskal function
    Edge *input = new Edge[E];
    for(int i = 0; i < E; i++) {
        input[i] = inputEdges[i];
    }
    
    // Call the kruskal function
    kruskal(input, n, E);
    

    delete[] input;
    file.close();
    
    return 0;
}