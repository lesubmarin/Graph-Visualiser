#include <iostream>
#include <vector>
#include <random>
#include <SDL2/SDL.h>

const int WindowWidth = 800;
const int WindowHeight = 600;
const int VertexRadius = 10;
const int edgethickness = 2;
int const numVertices = 10; // Change the number of vertices as needed
int const numEdges = 10; // Change the number of edges as needed

struct Vertex {
    int x;
    int y;
};

class Graph {
private:
    int numVertices;
    std::vector<Vertex> vertices;
    std::vector<std::vector<int>> adjacencyList;

public:
    Graph(int vertices) : numVertices(vertices) {
        adjacencyList.resize(numVertices);
    }

    int getNumVertices() const {
        return numVertices;
    }

    void addEdge(int source, int destination) {
        adjacencyList[source].push_back(destination);
        adjacencyList[destination].push_back(source); // Undirected graph
    }

    void generateRandomGraph(int numEdges) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> disX(0, WindowWidth);
        std::uniform_int_distribution<int> disY(0, WindowHeight);

        for (int i = 0; i < numVertices; ++i) {
            Vertex v;
            v.x = disX(gen);
            v.y = disY(gen);
            vertices.push_back(v);
        }

        for (int i = 0; i < numEdges; ++i) {
            int source = i % numVertices; // Start from the beginning if we exceed numVertices
            int destination = i + 1;
            if (destination >= numVertices) {
                destination = 0;
            }

            addEdge(source, destination);
        }
    }

    void drawGraph(SDL_Renderer* renderer, int edgethickness) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set drawing color to white
        SDL_RenderClear(renderer);

        // Draw edges
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set drawing color to black for edges
        for (int i = 0; i < numVertices; ++i) {
            for (int j : adjacencyList[i]) {
                SDL_RenderDrawLine(renderer, vertices[i].x, vertices[i].y, vertices[j].x, vertices[j].y);
            }
        }

        // Draw vertices
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set drawing color to red for vertices
        for (const auto& vertex : vertices) {
            SDL_Rect rect = { vertex.x - (VertexRadius / 2), vertex.y - (VertexRadius / 2), VertexRadius, VertexRadius };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
    }
};

void initializeSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (SDL_CreateWindowAndRenderer(WindowWidth, WindowHeight, 0, &window, &renderer) != 0) {
        std::cerr << "Window or renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    SDL_RenderSetLogicalSize(renderer, WindowWidth, WindowHeight);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    initializeSDL(window, renderer);

    Graph graph(numVertices);
    graph.generateRandomGraph(numEdges); // Generate a random graph with 10 edges

    graph.drawGraph(renderer, edgethickness);

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
