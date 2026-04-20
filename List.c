/***
* Allie Stein
* afstein
* 2026 Spring CSE101 PA1
* List.c
* List ADT implementation
***/ 


/*
Resources:
https://www.geeksforgeeks.org/c/doubly-linked-list-in-c/
https://people.ucsc.edu/~ptantalo/cse101/Winter26/Examples/C/
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// Structs --------------------------------------------------------------------

// creates a doubly linked list
typedef struct NodeObj {
    int data;             // stores an integer (an index)
    struct NodeObj* prev; // points to prev node
    struct NodeObj* next; // points to next node
} NodeObj;

typedef NodeObj* Node; // create node

// Heap memory
// listObj[front, cursor, back, position, length]

typedef struct ListObj {
    Node front; // front node or head of list
    Node back;  // back node or tail of list
    Node cursor; // the cursor or pointer
    int length;  // length of list
    int position; // position of cursor
} ListObj;

// Constructors-Destructors -----------------------------------------------------------

// newList()
// Creates a new empty list.
List newList(void) {

    // Stack memory
    List L = malloc(sizeof(ListObj));

    // initial values
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->position = -1;

    return L;
}

// freeList()
// Frees heap memory associated with *pL, sets *pL to NULL.
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {

        // Free all nodes in the list
        while (length(*pL) > 0) {
            deleteFront(*pL);
        }
        // Free the ListObj itself
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L) {
    return L->length;
}

// position()
// If cursor is defined, returns the position of the cursor element, otherwise
// returns -1.
int position(List L) {
    if (L->cursor != NULL) {
        return L->position;
    }
    else {
        return -1; // cursor is undefined
    }
}

// front()
// Returns front element. Pre: length()>0
ListElement front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    if (L->length > 0) {
        return L->front->data;
    }
    else {
        fprintf(stderr, "List Error: empty List\n");
        exit(EXIT_FAILURE);
    }
}

// back()
// Returns back element. Pre: length()>0
ListElement back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    if (L->length > 0) {
        return L->back->data;
    }
    else {
        fprintf(stderr, "List Error: empty List\n");
        exit(EXIT_FAILURE);
    }
}

// get()
// Returns cursor element. Pre: length()>0, position()>=0
ListElement get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    if (L->length > 0 && L->position >= 0) {
        return L->cursor->data;
    }
    else {
        fprintf(stderr, "List Error:empty list or undefined cursor\n");
        exit(EXIT_FAILURE);
    }
}

// equals()
// Returns true if A and B are the same integer sequence, false otherwise. The
// cursor is not altered in either List.
bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    // Check if lengths are equal
    if (A->length != B->length) {
        return false;
    }

    Node nodeA = A->front;
    Node nodeB = B->front;

    while (nodeA != NULL && nodeB != NULL) {
        if (nodeA->data != nodeB->data) {
            return false;
        }
        nodeA = nodeA->next;
        nodeB = nodeB->next;
    }

    return true;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    while (L->length > 0) {
        deleteFront(L);
    }
}

// set()
// Overwrites the cursor element’s data with x. Pre: length()>0, position()>=0
void set(List L, ListElement x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    if (L->length == 0 || L->position < 0) {
        fprintf(stderr, "List Error: undefined cursor or empty list\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;
}

// moveFront()
// If L is non-empty, places the cursor under the front element, otherwise does
// nothing.
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    if (L->length > 0) {
        L->cursor = L->front;
        L->position = 0;
    }
}

// moveBack()
// If List is non-empty, places the cursor under the back element, otherwise
// does nothing.
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    if (L->length > 0) {
        L->cursor = L->back;
        L->position = length(L) - 1;
    }
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward front of
// L, if cursor is defined and at front, cursor becomes undefined, if cursor is
// undefined does nothing.
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL && L->cursor->prev != NULL) {
        L->cursor = L->cursor->prev;
        L->position--;
    }
    else if (L->cursor != NULL) {
        L->cursor = NULL;
        L->position = -1;
    }

}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward back of
// L, if cursor is defined and at back, cursor becomes undefined, if cursor is
// undefined does nothing.
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor != NULL && L->cursor->next != NULL) {
        L->cursor = L->cursor->next;
        L->position++;
    }
    else if (L->cursor != NULL) {
        L->cursor = NULL;
        L->position = -1;
    }

}

// prepend()
// Insert new element into L. If List is non-empty, insertion takes place
// before front element.
void prepend(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    Node newNode = malloc(sizeof(NodeObj));
    if (newNode == NULL) {
        fprintf(stderr, "Node Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = L->front;

    if (L->front != NULL) {
        L->front->prev = newNode;
    }

    if (L->length == 0) {
        L->back = newNode;
    }

    L->front = newNode;
    L->length++;

    if (L->cursor != NULL) {
        L->position++;
    }
}

// append()
// Insert new element into L. If List is non-empty, insertion takes place
// after back element.
void append(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    Node newNode = malloc(sizeof(NodeObj));
    if (newNode == NULL) {
        fprintf(stderr, "Node Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = L->back;

    if (L->back != NULL) {
        L->back->next = newNode;
    }

    if (L->length == 0) {
        L->front = newNode;
    }

    L->back = newNode;
    L->length++;
}

// insertBefore()
// Insert new element before cursor. Pre: length()>0, position()>=0
void insertBefore(List L, ListElement data) {
    if (L == NULL || L->length <= 0 || L->cursor == NULL) {
        fprintf(stderr, "List Error: NULL, empty list, or undefined cursor\n");
        exit(EXIT_FAILURE);
    }


    Node newNode = malloc(sizeof(NodeObj));
    Node currentNode = L->cursor;

    if (newNode == NULL) {
        fprintf(stderr, "Node Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = currentNode;
    newNode->prev = currentNode->prev;

    if (currentNode->prev != NULL) {
        currentNode->prev->next = newNode;
    }
    else {
        L->front = newNode;
    }

    currentNode->prev = newNode;
    L->position++;
    L->length++;
}

// insertAfter()
// Inserts new element after cursor. Pre: length()>0, position()>=0
void insertAfter(List L, ListElement data) {
    if (L == NULL || L->length <= 0 || L->cursor == NULL) {
        fprintf(stderr, "List Error: NULL, empty list, or undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    Node newNode = malloc(sizeof(NodeObj));
    Node currentNode = L->cursor;

    newNode->data = data;
    newNode->prev = currentNode;
    newNode->next = currentNode->next;

    if (currentNode->next != NULL) {
        currentNode->next->prev = newNode;
    }
    else {
        L->back = newNode;
    }

    currentNode->next = newNode;
    L->length++;
}

// deleteFront()
// Deletes the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL || L->length <= 0) {
        fprintf(stderr, "List Error: NULL or empty list\n");
        exit(EXIT_FAILURE);
    }

    Node N = L->front;

    if (L->length > 1) {
        L->front = N->next;
        L->front->prev = NULL;

        if (L->cursor == N) {
            L->cursor = NULL;
            L->position = -1;
        } 
        
        else if (L->position != -1) {
            L->position--;
        }
    } 
    
    else {

        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->position = -1;
    }

    free(N);
    L->length--;
}

// deleteBack()
// Deletes the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL || L->length <= 0) {
        fprintf(stderr, "List Error: NULL or empty list\n");
        exit(EXIT_FAILURE);
    }

    Node N = L->back;

    if (L->length > 1) {
        L->back = N->prev;
        L->back->next = NULL;

        if (L->cursor == N) {
            L->cursor = NULL;
            L->position = -1;
        }
    } else {
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->position = -1;
    }

    free(N);
    L->length--;
}

// delete()
// Deletes cursor element, making cursor undefined. Pre: length()>0, position()>=0
void delete(List L) {
    if (L == NULL || L->length <= 0 || L->position < 0) {
        fprintf(stderr, "List Error: NULL or empty list\n");
        exit(EXIT_FAILURE);
    }

    // cursor at front
    if (L->cursor == L->front) {
        deleteFront(L);
    }
    // cursor at back
    else if (L->cursor == L->back) {
        deleteBack(L);
    }
    // cursor in middle
    else {
        Node N = L->cursor;

        N->prev->next = N->next;
        N->next->prev = N->prev;

        free(N);
        L->length--;
    }

    L->cursor = NULL;
    L->position = -1;
}

// Other operations -----------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a comma separated sequence
// of integers, surrounded by parentheses, with front on left, to the stream
// pointed to by out.
void printList(FILE* out, List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    fprintf(out, "(");
    Node N = L->front;
    while (N != NULL) {
        fprintf(out, "%d", N->data);
        if (N->next != NULL) fprintf(out, ", ");
        N = N->next;
    }
    fprintf(out, ")\n\n");
}

// copyList()
// Returns a new List representing the same integer sequence as L. The cursor
// in the new list is undefined, regardless of the state of the cursor in L. The
// List L is unchanged.
List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    List nL = newList();
    Node newNode = L->front;

    while (newNode != NULL) {
        append(nL, newNode->data);
        newNode = newNode->next;
    }

    return nL;
}

// join()
// Returns the concatenation of A followed by B. The cursor in the new List is
// undefined, regardless of the states of the cursors A in and B. The states of
// A and B are unchanged.
List join(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "List Error: NULL\n");
        exit(EXIT_FAILURE);
    }

    List J = newList();
    Node newNode = A->front;

    while (newNode != NULL) {
        append(J, newNode->data);
        newNode = newNode->next;
    }

    newNode = B->front;
    while (newNode != NULL) {
        append(J, newNode->data);
        newNode = newNode->next;
    }

    return J;
}

// split()
// Removes all elements before (in front of but not equal to) the cursor element
// in L. The cursor element in L is unchanged. Returns a new List consisting of
// all the removed elements. The cursor in the returned list is undefined.
// Pre: length(L)>0, position(L)>=0
List split(List L) {
    if (L == NULL || length(L) <= 0 || L->position < 0) {
        fprintf(stderr, "List Error: NULL, empty list, or undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    List rL = newList();
    Node newNode = L->front;

    while (newNode != L->cursor) {
        append(rL, newNode->data);
        newNode = newNode->next;
    }

    L->front = L->cursor;
    if (L->cursor != NULL) {
         L->cursor->prev = NULL;
    }

    L->length -= rL->length;

    return rL;
}

