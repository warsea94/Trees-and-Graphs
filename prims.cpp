#include "prims.hpp"
#include <vector>
#include <queue>
#include <limits> // Required for std::numeric_limits

// Constructor: initializes the graph with V vertices and resizes adjacency list
Prims::Prims(int vertices) : V(vertices) {
    adj.resize(V);
}

// Function to add an edge to the graph (undirected graph)
void Prims::addEdge(int u, int v, int weight) {
    // Add edge from u to v
    adj[u].push_back(AdjNode(v, weight));
    // Add edge from v to u (since graph is undirected)
    adj[v].push_back(AdjNode(u, weight));
}

// Function to find the Minimum Spanning Tree (MST) using Prim's algorithm
std::vector<MSTEdge> Prims::findMST(int startVertex) {
    std::vector<MSTEdge> mstEdges; // Stores edges of the MST

    // Min-priority queue to store pairs of (weight, vertex), ordered by weight
    // We use our AdjNode struct which has an overloaded operator> for min-heap behavior
    std::priority_queue<AdjNode, std::vector<AdjNode>, std::greater<AdjNode>> pq;

    // Vector to store the key (minimum weight) to reach each vertex from the MST
    std::vector<int> key(V, std::numeric_limits<int>::max());

    // Vector to store the parent of each vertex in the MST
    std::vector<int> parent(V, -1);

    // Vector to track if a vertex is included in MST
    std::vector<bool> inMST(V, false);

    // Start with the given startVertex
    if (V == 0) return mstEdges; // Handle empty graph
    if (startVertex < 0 || startVertex >= V) {
        // Invalid start vertex, perhaps start with 0 or return empty
        if (V > 0) startVertex = 0; // Default to 0 if invalid and graph not empty
        else return mstEdges;
    }


    pq.push(AdjNode(startVertex, 0));
    key[startVertex] = 0;

    while (!pq.empty()) {
        // Extract the vertex with the minimum key value
        AdjNode topNode = pq.top();
        pq.pop();
        int u = topNode.to;

        // If u is already in MST, skip (this handles cycles and redundant entries in PQ)
        if (inMST[u]) {
            continue;
        }

        // Include vertex u in MST
        inMST[u] = true;

        // If u is not the start vertex (which has no parent in this context)
        // and a parent exists, add the edge to MST
        if (parent[u] != -1) {
            mstEdges.push_back({parent[u], u, key[u]});
        }

        // Iterate through all adjacent vertices of u
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            // If v is not yet in MST and weight of (u,v) is smaller than current key of v
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;     // Update key of v
                pq.push(AdjNode(v, key[v])); // Add to priority queue
                parent[v] = u;       // Set u as parent of v
            }
        }
    }
    return mstEdges;
}
