#include "node.h"

#ifndef DRIV
#define DRIV
// Returns an interger from standard input.
int getInput(char *prompt);

// Prompts the user for index and integer then  inserts the element in the list.
node *DInsertElementAt(node *head);

// Prompts user for integer then appends the elemnent at the end. Returns head.
node *DInsertElement(node *head);

// Prints the list.
void DPrintList(node *head);

// Prints the lists size.
void DPrintListSize(node *head);

// Prompts user for an integer and removes the first instance in the list. Returns head.
node *DRemoveInteger(node *head);

// Prompts user for an index and removes the element at that index. Returns head.
node *DRemoveAt(node *head);

// Removes all elements in the list. Returns head.
node *DClear(node *head);

// Reverses the order of the list. Returns head.
node *DReverse(node *head);

// Moves the first integer to the last place in the list. Returns head.
node *DShiftLeft(node *head);

// Moves the last integer to the first place in the list. Returns head.
node *DShiftRight(node *head);

// Sorts the list in ascending order. Returns head.
node *DSort(node *head);

// Prints the address ofthe first node.
void DPrintStartAdress(node *head);

#endif