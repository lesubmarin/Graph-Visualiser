# Random Graph Visualization using SDL2

This project demonstrates the visualization of a random graph using SDL2 (Simple DirectMedia Layer) library in C++.

## Dependencies

- SDL2 library

## Usage

1. Compile the code using a C++ compiler that supports C++11 or later.
2. Make sure you have SDL2 library installed and linked correctly.
3. Run the compiled executable.
4. A window will open displaying a random graph with vertices and edges.

## Customization

- You can adjust the number of vertices and edges generated in the graph by modifying the parameters passed to the `Graph` class constructor and `generateRandomGraph` method.
- The thickness of the edges and radius of the vertices can be modified by changing the values of `EdgeThickness` and `VertexRadius` constants, respectively, in the code.
- You can customize the appearance of vertices and edges by changing the rendering colors in the `drawGraph` method of the `Graph` class.
