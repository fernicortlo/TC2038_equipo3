#include <iostream>
#include <vector>

struct disjoint_set {
    std::vector <int> parent; // vector to store the parent of each node
    std::vector <int> rank; // vector to store the rank of each node
    int n; // number of nodes in the set

    disjoint_set(int a) {
        n = a;
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
            rank.push_back(0);
        }
    }

    int find(int u) { // find the parent of a node
        if (parent[u] != u) { // if the node is not the parent of itself
            parent[u] = find(parent[u]); // find the parent of the parent of the node
        }
        return parent[u]; // return the parent of the node
    }
};


int main() {
    return 0;
}