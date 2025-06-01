#include <iostream>
#include "kruskal.hpp"

int main() {
    // Example graph with 4 vertices
    int numVertices = 4;
    Kruskal graph(numVertices);

    // Add edges: u, v, weight
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    std::cout << "Finding Minimum Spanning Tree..." << std::endl;
    std::vector<Edge> mst = graph.findMST();

    int totalWeight = 0;
    std::cout << "Edges in the MST:" << std::endl;
    for (const auto& edge : mst) {
        std::cout << "Edge: " << edge.u << " - " << edge.v << " weight: " << edge.weight << std::endl;
        totalWeight += edge.weight;
    }

    std::cout << "Total weight of MST: " << totalWeight << std::endl;

    // Example with a graph that might not be connected or has fewer edges than V-1
    std::cout << "\nExample with a different graph (5 vertices):" << std::endl;
    Kruskal graph2(5);
    graph2.addEdge(0, 1, 1);
    graph2.addEdge(1, 2, 2);
    graph2.addEdge(3, 4, 3); // This graph will have two components

    std::vector<Edge> mst2 = graph2.findMST();
    int totalWeight2 = 0;
    std::cout << "Edges in the MST2:" << std::endl;
    if (mst2.empty() && numVertices > 1) { // numVertices for graph2 is 5
        std::cout << "No spanning tree found (graph might be disconnected or have no edges)." << std::endl;
    } else {
        for (const auto& edge : mst2) {
            std::cout << "Edge: " << edge.u << " - " << edge.v << " weight: " << edge.weight << std::endl;
            totalWeight2 += edge.weight;
        }
        std::cout << "Total weight of MST2: " << totalWeight2 << std::endl;
        if (mst2.size() < 5 - 1 && 5 > 1) {
             std::cout << "Note: The graph might be disconnected, so a spanning forest is found." << std::endl;
        }
    }


    return 0;
}
