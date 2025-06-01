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

-   **`main.cpp`**: This file (renamed to `main-kruskal.cpp` for clarity, or kept as `main.cpp` if it's the primary demo) serves as an entry point and contains test cases for Kruskal's algorithm.
    -   It creates instances of the `Kruskal` class.
    -   Edges are added, `findMST()` is called, and results are printed.
    -   Includes examples for connected and disconnected graphs (resulting in a spanning forest).

---

# Prim's Algorithm for Minimum Spanning Tree

This section details a C++ implementation of Prim's algorithm, also used to find the Minimum Spanning Tree (MST) of an undirected graph.

## Files

-   **`prims.hpp`**: This header file defines structures and classes for Prim's algorithm.
    -   `struct AdjNode`: Represents a node in the adjacency list, storing the destination vertex (`to`) and the edge's `weight`. It includes a comparator `operator>` to allow `std::priority_queue` to function as a min-priority queue.
    -   `struct MSTEdge`: Represents an edge in the MST, containing `u`, `v`, and `weight`. Used for returning the resulting MST.
    -   `class Prims`: Encapsulates Prim's algorithm logic.
        -   `Prims(int vertices)`: Constructor, initializes the graph with `V` vertices and prepares the adjacency list.
        -   `addEdge(int u, int v, int weight)`: Adds an undirected edge to the graph by updating the adjacency lists for both `u` and `v`.
        -   `findMST(int startVertex)`: Executes Prim's algorithm starting from `startVertex`. It uses a min-priority queue to select the next edge to add, a `key` vector to store minimum edge weights to reach vertices, and a `parent` vector to reconstruct the MST. It finds an MST for the connected component containing the `startVertex`.

-   **`prims.cpp`**: This source file contains the implementations for the methods of the `Prims` class declared in `prims.hpp`.

-   **`main-prims.cpp`**: This file serves as an entry point for testing the Prim's algorithm implementation.
    -   It creates `Prims` class instances for various graph configurations.
    -   Edges are added, and `findMST()` is called with a starting vertex.
    -   The resulting MST edges and total weight are printed.
    -   Includes examples for connected graphs, graphs where Prim's finds an MST for the component of the start vertex, single-vertex graphs, and graphs with no edges.

---

## How to Compile and Run

You'll need a C++ compiler that supports C++11 or later (e.g., g++).

### Kruskal's Algorithm

1.  **Compile the code:**
    (Assuming `main.cpp` is the test file for Kruskal, or use `main-kruskal.cpp` if you've named it so)
    ```sh
    g++ -std=c++11 main.cpp kruskal.cpp -o kruskal_test
    ```

2.  **Run the executable:**
    ```sh
    ./kruskal_test
    ```
    Or on Windows: `.\kruskal_test.exe`

The program will output the MST details from `main.cpp`.

### Prim's Algorithm

1.  **Compile the code:**
    ```sh
    g++ -std=c++11 main-prims.cpp prims.cpp -o prims_test
    ```

2.  **Run the executable:**
    ```sh
    ./prims_test
    ```
    Or on Windows: `.\prims_test.exe`

The program will output the MST details from `main-prims.cpp`.
