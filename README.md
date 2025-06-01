# Kruskal's Algorithm for Minimum Spanning Tree

This repository contains a C++ implementation of Kruskal's algorithm to find the Minimum Spanning Tree (MST) of a given undirected graph.

## Files

-   **`kruskal.hpp`**: This header file defines the necessary structures and classes for the algorithm.
    -   `struct Edge`: Represents an edge in the graph, containing the source (`u`), destination (`v`), and weight of the edge. It includes a comparator to sort edges by weight.
    -   `class Kruskal`: Encapsulates the logic for Kruskal's algorithm. It includes methods to add edges to the graph, find the parent of a node (for the Disjoint Set Union - DSU data structure), unite two sets of nodes, and execute the algorithm to find the MST.

-   **`kruskal.cpp`**: This source file provides the implementation for the methods declared in the `Kruskal` class in `kruskal.hpp`.
    -   `Kruskal(int vertices)`: Constructor that initializes the graph with a given number of vertices.
    -   `addEdge(int u, int v, int weight)`: Adds an edge with its weight to the graph.
    -   `findParent(int i)`: A helper function for the DSU data structure, used to find the representative (parent) of the set containing node `i`. Implements path compression for efficiency.
    -   `uniteSets(int u, int v)`: A helper function for the DSU data structure, used to merge the sets containing nodes `u` and `v`. Implements union by rank/size implicitly by always making one parent point to another.
    -   `findMST()`: Executes Kruskal's algorithm. It sorts all edges by weight and then iterates through them, adding an edge to the MST if it connects two previously disconnected components (checked using the DSU structure). It returns a vector of `Edge` objects representing the MST.

-   **`main.cpp`**: This file serves as the entry point of the program and contains test cases to demonstrate the functionality of the Kruskal's algorithm implementation.
    -   It creates instances of the `Kruskal` class for different graph configurations.
    -   Edges are added to these graphs.
    -   The `findMST()` method is called to compute the MST.
    -   The edges of the MST and its total weight are printed to the console.
    -   Includes examples for a connected graph and a graph that results in a minimum spanning forest (if components are disconnected).

## How to Compile and Run

To compile and run the program, you'll need a C++ compiler that supports C++11 or later (e.g., g++).

1.  **Compile the code:**
    Open a terminal or command prompt, navigate to the directory containing the files, and run the following command:
    ```sh
    g++ -std=c++11 main.cpp kruskal.cpp -o kruskal_test
    ```

2.  **Run the executable:**
    After successful compilation, an executable file named `kruskal_test` (or `kruskal_test.exe` on Windows) will be created. Run it using:
    ```sh
    ./kruskal_test
    ```
    Or on Windows:
    ```sh
    .\kruskal_test.exe
    ```

The program will then output the edges included in the Minimum Spanning Tree and the total weight of the MST for the predefined test cases in `main.cpp`.
