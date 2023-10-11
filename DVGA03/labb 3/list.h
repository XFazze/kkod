#include "node.h"
#ifndef LIST
#define LIST

// Calculerar storleken på headan. Antalet noder.
int LSize(node *head);

// Kontrollerar ifall headan är tom. Returnerar 1 för tom och 0 för icke-tom.
int LIsEmpty(node *head);

// Returnerar ett element från ett visst index i headan. Returnerar -1 ifall elementet inte finns.
node *LGetNode(node *head, int index);

// Returnerar 1 ifall värdet finns i headan annars 0.
int LContains(node *head, int value);

// Returnerar indexet vid första förekomsten av ett värde. Returnerar -1 ifall elementet inte finns.
int LGetFirstIndexOf(node *head, int value);

// Lägger till ett värde på en viss plats i headan.
node *LInsertElement(node *head, int value, int index);

// Tar bort ett element på en viss plats i headan.
node *LRemoveAtIndex(node *head, int index);

// Sorterar i stigande ordning
node *LSort(node *head);

// Returnerar nästa node
node *LGetNext(node *cnode);

// Returnerar väret på noden
int LGetValue(node *cnode);

// Recursive function reversing the order of the list.
node *LReverse(node *cnode, int depth);
#endif