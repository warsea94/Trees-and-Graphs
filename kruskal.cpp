#include "kruskal.hpp"
#include <numeric> // Required for std::iota

// Constructor: initializes the graph with V vertices
Kruskal::Kruskal(int vertices) : V(vertices) {
    parent.resize(V);
    // Initialize each vertex to be its own parent (for DSU)
    std::iota(parent.begin(), parent.end(), 0);
}

// Function to add an edge to the graph
void Kruskal::addEdge(int u, int v, int weight) {
    edges.push_back({u, v, weight});
}

// Helper function for DSU: find the parent of a node (with path compression)
int Kruskal::findParent(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = findParent(parent[i]);
}

// Helper function for DSU: unite two sets (using union by rank/size could be an optimization)
void Kruskal::uniteSets(int u, int v) {
    int rootU = findParent(u);
    int rootV = findParent(v);
    if (rootU != rootV) {
        parent[rootU] = rootV; // Simple union: make one root parent of the other
    }
}

// Function to find the Minimum Spanning Tree (MST) using Kruskal's algorithm
std::vector<Edge> Kruskal::findMST() {
    std::vector<Edge> mst; // Stores the edges of the MST

    // Sort all edges by weight in non-decreasing order
    std::sort(edges.begin(), edges.end());

    int edgesCount = 0; // Counter for edges added to MST
    for (const auto& edge : edges) {
        // If including this edge does not form a cycle
        if (findParent(edge.u) != findParent(edge.v)) {
            uniteSets(edge.u, edge.v); // Include the edge and unite the sets
            mst.push_back(edge);
            edgesCount++;
            // MST is complete when it has V-1 edges
            if (edgesCount == V - 1)
                break;
        }
    }
    return mst;
}
