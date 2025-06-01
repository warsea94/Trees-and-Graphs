#ifndef PRIMS_HPP
#define PRIMS_HPP

#include <vector>
#include <queue>    // For std::priority_queue
#include <limits>   // For std::numeric_limits

// Structure to represent a node in the adjacency list
struct AdjNode {
    int to;
    int weight;

    // Constructor
    AdjNode(int t, int w) : to(t), weight(w) {}

    // Overload operator> for min-priority queue
    // (priority_queue by default is a max-heap)
    bool operator>(const AdjNode& other) const {
        return weight > other.weight;
    }
};

// Structure to represent an edge in the MST (for returning the result)
// Similar to Kruskal's Edge, but might be used differently if we only store MST edges
struct MSTEdge {
    int u, v, weight;
};

// Class to implement Prim's algorithm
class Prims {
public:
    // Constructor: takes the number of vertices
    Prims(int vertices);

    // Function to add an edge to the graph
    // For Prim's, this will build an adjacency list
    void addEdge(int u, int v, int weight);

    // Function to find the Minimum Spanning Tree (MST) using Prim's algorithm
    // Takes the starting vertex for Prim's algorithm as input
    std::vector<MSTEdge> findMST(int startVertex);

private:
    int V; // Number of vertices
    // Adjacency list representation of the graph
    // Each element is a vector of AdjNodes connected to the vertex i
    std::vector<std::vector<AdjNode>> adj;
};

#endif // PRIMS_HPP
