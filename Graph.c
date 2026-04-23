/***
* Allie Stein
* afstein
* 2026 Spring CSE101 PA2
* Graph.c
* Graph ADT implementation
***/ 

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#include "List.h"

// define struct GraphObj
typedef struct GraphObj {   

    List* adj;      // Adj lists - An array of Lists whose 𝑖th element contains the neighbors of vertex 𝑖.
    int* color;     // BFS color - An array of ints (or chars, or strings) whose 𝑖th element is the color (white, gray, black) of vertex 𝑖
    int* parent;    // BFS parent - An array of ints whose 𝑖th element is the parent of vertex 𝑖
    int* dist;      // BFS distance - An array of ints whose 𝑖th element is the distance from the (most recent) source to vertex 𝑖.

    int order;      // Num of vertices
    int numEdges;   // Num of edges (undirected)
    int numArcs;    // Dum of directed edges
    int source;     // BFS source (starting point)

} GraphObj;


// Colors for BFS
#define WHITE 0
#define GRAY 1
#define BLACK 2

// constructors - destructors -------------------------------------------------

// newGraph()
// Returns a Graph having n vertices and no edges.
Graph newGraph(int n) {
    Graph G = calloc(1, sizeof(GraphObj));

    if (G == NULL) {
        fprintf(stderr, "Graph Error: NULL\n");
        exit(EXIT_FAILURE);
    }


    // n = the num of vertices

    // Arrays are set to length (n + 1)
    int size = n + 1;

    // Create memory for arrays
    G->adj = calloc(size, sizeof(List));
    G->color = calloc(size, sizeof(int));
    G->parent = calloc(size, sizeof(int));
    G->dist = calloc(size, sizeof(int));

    // Init 
    G->order = n;
    G->numEdges = 0;
    G->numArcs = 0;
    G->source = NIL;


    // Init arrays indices 1-n 
    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->dist[i] = 0;
    }

    // Return graph
    return G;
}

// freeGraph()
// Frees all dynamic memory associated with Graph *pG and sets *pG to NULL.
void freeGraph(Graph* pG) {

    if (pG != NULL && *pG != NULL) {
        Graph G = *pG;

        // Free list - clear memory (from List)
        for (int i = 1; i <= getOrder(G); i++) {
            freeList(&G->adj[i]);
        }

        free(G->adj);
        free(G->color);
        free(G->parent);
        free(G->dist);
        free(G);

        *pG = NULL;
    }
}

// access functions -----------------------------------------------------------

// getOrder()
// Returns the number of vertices in G.
int getOrder(Graph G) {
    return G->order;
}

// getNumEdges()
// Returns the number of edges in G.
int getNumEdges(Graph G) {
    return G->numEdges;
}

// getNumArcs()
// Returns the number of Arcs in G.
int getNumArcs(Graph G) {
    return G->numArcs;
}

// getSource()
// Returns the source vertex in the most recent call to BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G) {

    if (G->source != NIL) {
        return G->source;
    }
    else {
        return NIL;
    }
}

// getParent()
// Returns the parent of vertex u in the most recently constructed BFS tree
// or returns NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {

    // if (u < 1 || u > getOrder(G)) {
    //     fprintf(stderr, "Graph Error: \n");
    //     exit(EXIT_FAILURE);
    // }
    
    if (G->source != NIL) {
        return G->parent[u];
    } else {
        return NIL;
    }
}

// getDist()
// Returns the distance from the source vertex to u if BFS() has been called,
// otherwise returns INF.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {

    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: out of bounds\n");
        exit(EXIT_FAILURE);
    }

    if (G->source != NIL) {
        return G->dist[u];
    } else {
        return INF;
    }
}


// getPath()
// If vertex u is reachable from the source, appends the vertices of a shortest
// source-u path to List L. Otherwise, appends NIL to L.
// Pre: 1 <= u <= getOrder(G), getSource(G) != NIL
void getPath(List L, Graph G, int u) {

    // Check bounds
    if (!(1 <= u && u <= getOrder(G))) {
        append(L, NIL);
        return;
    }

    if (getSource(G) == NIL) {
        append(L, NIL);
        return;
    }

    // Check if u is reachable from source
    if (getDist(G, u) == INF) {
        // u is not reachable
        append(L, NIL);
    } else {
        if (u == getSource(G)) {
            append(L, u);
        } else if (getParent(G, u) == NIL) {
            append(L, NIL);
        } else {
            getPath(L, G, getParent(G, u));
            append(L, u);
        }
    }
}

// manipulation procedures ----------------------------------------------------

// makeNull()
// Resets G to its initial state.
void makeNull(Graph G) {

    // clear vertices (from List)
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->adj[i]);
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }

    G->numEdges = 0;
    G->numArcs = 0;
    G->source = NIL;
}

// addEdge()
// Creates an undirected edge joining vertex u to vertex v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
    if ((1 <= u && u <= getOrder(G)) && (1 <= v && v <= getOrder(G))) {


        // Sort into order for adj list


        moveFront(G->adj[u]);
        
        // Move while current element is LESS than v
        while (position(G->adj[u]) >= 0 && get(G->adj[u]) < v) {
            moveNext(G->adj[u]);
        }

        if (position(G->adj[u]) >= 0) {
            insertBefore(G->adj[u], v);
        } else {
            append(G->adj[u], v);
        }

        // Do the same for v
        moveFront(G->adj[v]);
        while (position(G->adj[v]) >= 0 && get(G->adj[v]) < u) {
            moveNext(G->adj[v]);
        }

        if (position(G->adj[v]) >= 0) {
            insertBefore(G->adj[v], u);
        } else {
            append(G->adj[v], u);
        }

        G->numEdges++;
    }
}



// addArc()
// Creates a directed edge joining vertex u to vertex v.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v) {

    if ((1 <= u && u <= getOrder(G)) && (1 <= v && v <= getOrder(G))) {
      // Sort into order for adj list


        moveFront(G->adj[u]);
        
        // Move while current element is LESS than v
        while (position(G->adj[u]) >= 0 && get(G->adj[u]) < v) {
            moveNext(G->adj[u]);
        }

        if (position(G->adj[u]) >= 0) {
            insertBefore(G->adj[u], v);
        } else {
            append(G->adj[u], v);
        }

        G->numArcs++;
    }
}



// BFS()
// Runs the Breadth First Search algorithm on G with source vertex s.
// Pre: 1 <= s <= getOrder(G)

void BFS(Graph G, int s) {
    if (!(s >= 1 && s <= getOrder(G))) {
        fprintf(stderr, "Graph Error: out of bounds\n");
        exit(EXIT_FAILURE);
    }

    // Set all vertices to undiscovered (white)
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->dist[i] = INF;
        G->parent[i] = NIL;
    }

    G->color[s] = GRAY;
    G->dist[s] = 0;
    G->source = s;
    G->parent[s] = NIL;

    List Q = newList();
    append(Q, s);

    while (length(Q) > 0) {

        int fQ = front(Q);
        deleteFront(Q);

        moveFront(G->adj[fQ]);

        while (position(G->adj[fQ]) >= 0) {
            int cV = get(G->adj[fQ]);

            if (G->color[cV] == WHITE) {
                G->color[cV] = GRAY;
                G->dist[cV] = G->dist[fQ] + 1;
                G->parent[cV] = fQ;
                append(Q, cV);
            }

            moveNext(G->adj[fQ]);
        }

        G->color[fQ] = BLACK;
    }

    freeList(&Q);
}

// other functions ------------------------------------------------------------

// printGraph()
// Prints the adjacency list representation of G to FILE* out.
void printGraph(FILE* out, Graph G) {

    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
    }
}



