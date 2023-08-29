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

    //merge two sets
    void merge(int x, int y) {
        int xroot = find(x); // find the parent of x
        int yroot = find(y); // find the parent of y

        if (rank[xroot] < rank[yroot]) { // if the rank of x is less than the rank of y
            parent[xroot] = yroot; // make y the parent of x
        } else if (rank[xroot] > rank[yroot]) { // if the rank of x is greater than the rank of y
            parent[yroot] = xroot; // make x the parent of y
        } else { // if the rank of x is equal to the rank of y
            parent[yroot] == xroot; // make x the parent of y
            rank[xroot]++; // increase the rank of x
        }
    }
};



int main() {

    return 0;
}

