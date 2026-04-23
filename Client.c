
/***
* Client.c
* Test client for List ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"



void printReverse(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    for (moveBack(L); position(L) >= 0; movePrev(L)) {
        printf("%d ", get(L));  // prints list in reverse
    }

}

void reverse(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    List copy = newList();

    // build reversed copy
    for (moveFront(L); position(L) >= 0; moveNext(L)) {
        prepend(copy, get(L));
    }

    // clear original list
    clear(L);

    // copy back into L
    for (moveFront(copy); position(copy) >= 0; moveNext(copy)) {
        append(L, get(copy));
    }

    freeList(&copy);
}

bool isPalindrome(List L){

    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    bool eq;
    List R = newList();

    for (moveFront(L); position(L) >= 0; moveNext(L)) {
        prepend(R, get(L));
    }

    eq = equals(L, R);
    freeList(&R);
    return eq;
}

// bool isPalindrome(List L) {
//     if (L == NULL) {
//         fprintf(stderr, "List Error: NULL\n");
//         exit(EXIT_FAILURE);
//     }

//     List copy = newList();

//     // build reversed copy
//     for (moveFront(L); position(L) >= 0; moveNext(L)) {
//         prepend(copy, get(L));
//     }

//     // reset cursors before comparing
//     moveFront(L);

//     for (moveFront(copy); position(copy) >= 0; moveNext(copy)) {
//         if (position(L) < 0 || get(L) != get(copy)) {
//             freeList(&copy);
//             return false;
//         }
//         moveNext(L);
//     }

//     freeList(&copy);
//     return true;
// }


void replace(List L, int x, int y) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    for (moveFront(L); position(L) >= 0; moveNext(L)) {
        if (get(L) == x) {
            set(L, y);
        }
    }


}

int getElementAt(List L, int i) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    if (i < 0 || i >= length(L)) {
        fprintf(stderr, "List Error: invalid index\n");
        exit(EXIT_FAILURE);
    }

    moveFront(L);

    for (int j = 0; j < i; j++) {
        moveNext(L);
    }

    return get(L);
}


int countComponents(Graph G) {
    int components = 0;
    int n = getOrder(G);       // number of vertices
    int visited[n + 1];        // visited array, 1-based indexing

    // initialize all vertices as unvisited
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    // iterate through all vertices
    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            components++;

            // Perform BFS starting at vertex i
            BFS(G, i);

            // Mark all vertices visited by BFS
            for (int j = 1; j <= n; j++) {
                if (getDist(G, j) != INF) {   // getDist returns distance from BFS source
                    visited[j] = 1;
                }
            }
        }
    }

    return components;
}


int countDFSComponents(Graph G) {
    int components = 0;
    int n = getOrder(G);

    List S = newList();

    // initialize list with vertices 1..n
    for (int i = 1; i <= n; i++) {
        append(S, i);
    }

    // run DFS
    DFS(G, S);

    // count roots of DFS forest
    for (moveFront(S); position(S) >= 0; moveNext(S)) {
        if (getParent(G, get(S)) == NIL) {
            components++;
        }
    }

    freeList(&S);
    return components;
}


int main(void) {

    // Create a new list
    List L = newList();

    printf("Appending integers 1 to 5 to the list...\n");
    for (int i = 1; i <= 5; i++) {
        append(L, i);
    }
    printList(stdout, L);

    printf("\n");


    printf("Reverse the list using printReverse()\n");
    printReverse(L);

    printf("\n");

    printf("\nReversing the list using reverse()...\n");
    reverse(L);
    printList(stdout, L);

    printf("\n");


    printf("Checking if the list is a palindrome...\n");
    if (isPalindrome(L)) {
        printf("The list is a palindrome.\n");
    } else {
        printf("The list is not a palindrome.\n");
    }
    printf("\n");

    printf("replace 3 with 99...\n");
    replace(L, 3, 99);
    printList(stdout, L);


    printf("\n");

    printf("Element at index 2: %d\n", getElementAt(L, 2));
    printf("Element at index 0: %d\n", getElementAt(L, 0));

    printf("\n");

    printf("Creating a graph with 5 vertices...\n");
    Graph G = newGraph(5);
    printf("Adding edges (1-2), (1-3), (4-5)...\n");
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 4, 5);
    printf("Number of components in the graph: %d\n", countComponents(G));

    

    // Free memory
    freeList(&L);

    return 0;
}

