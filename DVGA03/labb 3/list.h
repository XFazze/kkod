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

// Lägger till ett värde på en viss plats i headan. Index måste vara lika eller mindre än storleken på listan.
node *LInsertElement(node *head, int value, int index);

// Tar bort ett element på en viss plats i headan. Index måste vara mindre än storleken på listan.
node *LRemoveAtIndex(node *head, int index);

// Sorterar i stigande ordning. Listans storlek måste vara minst 2.
node *LSort(node *head);

// Returnerar nästa node. Nästa node måste finnas.
node *LGetNext(node *cnode);

// Returnerar väret på noden. Noden måste ha ett värde.
int LGetValue(node *cnode);

// Rekursiv funktion som vänder på listan. LIstans måste innehålla minst ett värde.
node *LReverse(node *cnode, int depth);
#endif