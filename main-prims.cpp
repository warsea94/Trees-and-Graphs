#include <iostream>
#include "prims.hpp"
#include <vector> // For std::vector
#include <numeric> // For std::accumulate (optional, for summing weight)

int main() {
    std::cout << "Prim's Algorithm MST Test" << std::endl;

    // Example 1: Connected graph
    int numVertices1 = 4;
    Prims graph1(numVertices1);

    // Add edges: u, v, weight
    graph1.addEdge(0, 1, 10);
    graph1.addEdge(0, 2, 6);
    graph1.addEdge(0, 3, 5);
    graph1.addEdge(1, 3, 15);
    graph1.addEdge(2, 3, 4);

    int startVertex1 = 0;
    std::cout << "\nGraph 1 (Connected): Finding MST starting from vertex " << startVertex1 << std::endl;
    std::vector<MSTEdge> mst1 = graph1.findMST(startVertex1);

    int totalWeight1 = 0;
    std::cout << "Edges in the MST for Graph 1:" << std::endl;
    if (mst1.empty() && numVertices1 > 1) {
        std::cout << "No MST found (graph might be disconnected or have no edges from start vertex)." << std::endl;
    } else {
        for (const auto& edge : mst1) {
            std::cout << "Edge: " << edge.u << " - " << edge.v << " weight: " << edge.weight << std::endl;
            totalWeight1 += edge.weight;
        }
        std::cout << "Total weight of MST for Graph 1: " << totalWeight1 << std::endl;
        // A complete MST should have V-1 edges for a connected graph
        if (mst1.size() != numVertices1 - 1 && numVertices1 > 0) {
            std::cout << "Note: MST does not have V-1 edges. Graph might be disconnected or start vertex isolated." << std::endl;
        }
    }

    // Example 2: Graph that might be disconnected if not all parts are reachable from startVertex
    // Prim's finds MST for the component connected to startVertex.
    int numVertices2 = 5;
    Prims graph2(numVertices2);
    graph2.addEdge(0, 1, 1); // Component 1
    graph2.addEdge(1, 2, 2); // Component 1
    graph2.addEdge(0, 2, 3); // Component 1
    graph2.addEdge(3, 4, 5); // Component 2 (isolated from vertex 0)

    int startVertex2 = 0;
    std::cout << "\nGraph 2 (Potentially Disconnected Components): Finding MST starting from vertex " << startVertex2 << std::endl;
    std::vector<MSTEdge> mst2 = graph2.findMST(startVertex2);

    int totalWeight2 = 0;
    std::cout << "Edges in the MST for Graph 2 (component of vertex " << startVertex2 << "):" << std::endl;
    if (mst2.empty()) {
        if (numVertices2 == 1) {
            std::cout << "Single vertex graph, no edges in MST." << std::endl;
        } else if (numVertices2 > 1) {
            // Check if the start vertex is actually isolated or if the component has no edges
            // This is tricky without knowing the graph structure, Prim's should just return empty if no edges can be added.
            std::cout << "No MST found starting from vertex " << startVertex2
                      << ". The vertex might be isolated, or its component has no other reachable edges, or the graph is empty." << std::endl;
        }
        // If numVertices2 is 0, findMST should return empty, and this block handles it gracefully.
    } else {
        for (const auto& edge : mst2) {
            std::cout << "Edge: " << edge.u << " - " << edge.v << " weight: " << edge.weight << std::endl;
            totalWeight2 += edge.weight;
        }
        std::cout << "Total weight of MST for Graph 2 (component of vertex " << startVertex2 << "): " << totalWeight2 << std::endl;
        // For this specific test case (Graph 2, starting at 0), the component of vertex 0 has vertices {0,1,2}.
        // It should have 2 edges in its MST.
        if (startVertex2 == 0 && numVertices2 == 5) { // Highly specific check for this test case
            int expectedEdgesInComponent = 2; // Vertices 0,1,2 form a component
            if (mst2.size() != expectedEdgesInComponent) {
                std::cout << "Note: Expected " << expectedEdgesInComponent << " edges for the component of vertex "
                          << startVertex2 << ", but found " << mst2.size() << "." << std::endl;
            }
        }
    }


    // Example 3: Single vertex graph
    std::cout << "\nGraph 3 (Single Vertex):" << std::endl;
    Prims graph3(1);
    std::vector<MSTEdge> mst3 = graph3.findMST(0);
    std::cout << "Edges in MST for single vertex graph: " << mst3.size() << std::endl;
    std::cout << "Total weight: 0" << std::endl;


    // Example 4: Graph with no edges
    std::cout << "\nGraph 4 (Multiple Vertices, No Edges):" << std::endl;
    Prims graph4(3);
    std::vector<MSTEdge> mst4 = graph4.findMST(0);
    std::cout << "Edges in MST for graph with no edges: " << mst4.size() << std::endl;
    std::cout << "Total weight: 0" << std::endl;


    return 0;
}
