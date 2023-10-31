// This code is the dijkstra algortihm implementation in C++.
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Define the Infinite value for the distance.
const int INF = numeric_limits<int>::max();

// This pair is for the priority queue to hold pairs of (dist, node).
using pii = pair<int, int>;

void dijkstra(const vector<vector<pii>>& graph, int source) {
    // vertices
    int V = graph.size();

    // The distance vector that holds the shortest distance from source to i
    vector<int> dist(V, INF);

    // Using priority_queue to get the minimum distance vertex efficiently.
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Push the source with distance 0 into the queue.
    pq.push(make_pair(0, source));
    dist[source] = 0;

    while (!pq.empty()) {
        // The first vertex in pair is the minimum distance vertex.
        int u = pq.top().second;
        pq.pop();

        // Visit all the adjacent vertices of u.
        for (const auto& adj : graph[u]) {
            int v = adj.first;
            int weight = adj.second;

            // If there is a shorter path to v through u.
            if (dist[v] > dist[u] + weight) {
                // Updating the distance of v.
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    // Print shortest distances from source.
    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < V; ++i)
        cout << i << "\t\t" << ((dist[i] == INF) ? "INF" : to_string(dist[i])) << endl;
}

int main() {
    // Number of vertices.
    int V = 5;
    // Graph is represented as an adjacency list of (node, weight).
    vector<vector<pii>> graph(V, vector<pii>());

    // Add edges.
    graph[0].push_back(make_pair(1, 3)); // Edge: 0 - 1, weight: 3
    graph[0].push_back(make_pair(3, 8));
    graph[0].push_back(make_pair(4, 7));
    graph[1].push_back(make_pair(2, 1));
    graph[2].push_back(make_pair(3, 4));
    graph[3].push_back(make_pair(0, 8));
    graph[3].push_back(make_pair(4, 3));
    graph[4].push_back(make_pair(0, 7));

    // Starting Dijkstra's algorithm from vertex 0.
    dijkstra(graph, 0);

    return 0;
}