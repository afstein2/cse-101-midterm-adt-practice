
/***
* Client.c
* Test client for List ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"



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

int main(void) {

    // Create a new list
    List L = newList();

    printf("Appending integers 1 to 5 to the list...\n");
    for (int i = 1; i <= 5; i++) {
        append(L, i);
    }
    printList(stdout, L);


    printf("Reverse the list using printReverse()\n");
    printReverse(L);
    
    printf("\nReversing the list using reverse()...\n");
    reverse(L);
    printList(stdout, L);




    // Free memory
    freeList(&L);

    return 0;
}

