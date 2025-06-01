#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <vector>
#include <algorithm> // Required for std::sort

// Structure to represent a graph edge
struct Edge {
    int u, v, weight;

    // Comparator for sorting edges by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Class to implement Kruskal's algorithm
class Kruskal {
public:
    // Constructor: takes the number of vertices in the graph
    Kruskal(int vertices);

    // Function to add an edge to the graph
    void addEdge(int u, int v, int weight);

    // Function to find the Minimum Spanning Tree (MST) using Kruskal's algorithm
    std::vector<Edge> findMST();

private:
    int V; // Number of vertices
    std::vector<Edge> edges; // Vector to store all edges
    std::vector<int> parent; // Vector for disjoint set union (DSU)

    // Helper function for DSU: find the parent of a node
    int findParent(int i);

    // Helper function for DSU: unite two sets
    void uniteSets(int u, int v);
};

#endif // KRUSKAL_HPP
