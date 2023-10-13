#include "node.h"
#ifndef LIST
#define LIST

// Calculerar storleken på listan. Antalet noder.
int LSize(node *head);

// Kontrollerar ifall headan är tom. Returnerar 1 för tom och 0 för icke-tom.
int LIsEmpty(node *head);

// Returnerar en node från ett visst index i listan. Noden måste finnas.
node *LGetNode(node *head, int index);

// Returnerar 1 ifall värdet finns i headan annars 0.
int LContains(node *head, int value);

// Returnerar indexet vid första förekomsten av ett värde. Returnerar -1 ifall elementet inte finns.
int LGetFirstIndexOf(node *head, int value);

// Lägger till ett värde på en viss plats i headan. Index måste vara lika eller mindre än storleken på listan.
// Returnerar head.
node *LInsertElement(node *head, int value, int index);

// Tar bort ett element på en viss plats i headan. Index måste vara mindre än storleken på listan.
// Returnerar head.
node *LRemoveAtIndex(node *head, int index);

// Sorterar i stigande ordning. Listans storlek måste vara minst 2. Returnerar head.
node *LSort(node *head);

// Returnerar nästa node. Noden och nästa node måste finnas. Returnerar head.
node *LGetNext(node *cnode);

// Returnerar väret på noden. Noden måste finnsa och ha ett värde.
int LGetValue(node *cnode);

// Rekursiv funktion som vänder på listan. Listan måste innehålla minst ett värde. Returnerar head.
node *LReverse(node *cnode, int depth);
#endif