#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "driv.h"
#include "list.h"
#include "node.h"

#define MAX_INPUT 4
int getInput(char* prompt)
{
    char interger_buffer[MAX_INPUT];
    printf("%s:", prompt);
    fgets(interger_buffer, MAX_INPUT, stdin);
    strtok(interger_buffer, "\n");
    return atoi(interger_buffer);
}

node* DInsertElementAt(node* head)
{
    int heltal = getInput("Heltal");
    int index = getInput("Index");

    int size = LSize(head);
    if (size < index)
    {
        printf("Invalid operation: Index must be withtin the list or at the end.\n");
        return head;
    }
    return LInsertElement(head, heltal, index);
}

node* DInsertElement(node* head)
{
    int heltal = getInput("Heltal");

    return LInsertElement(head, heltal, LSize(head));
}

void DPrintList(node* head)
{
    printf("in list function");
    if (LIsEmpty(head))
    {
        printf("List is empty\n");
        return;
    }
    node* cnode = head;
    do
    {
        printf("%d ", LGetValue(cnode));
        cnode = LGetNext(cnode);
    } while (cnode != 0);
    printf("\n");
}

void DPrintListSize(node* head)
{
    printf("List size:%d\n", LSize(head));
}

node* DRemoveInteger(node* head)
{
    int heltal = getInput("Heltal");

    int index = LGetFirstIndexOf(head, heltal);
    if (index == -1)
    {
        printf("Invalid operation: Integer not in list.\n");
        return head;
    }
    return LRemoveAtIndex(head, index);
}

node* DRemoveAt(node* head)
{
    int index = getInput("Index");

    if (index >= LSize(head))
    {
        printf("Invalid operation: Index not in list.\n");
        return head;
    }
    return LRemoveAtIndex(head, index);
}

node* DClear(node* head)
{
    while (!LIsEmpty(head))
        head = LRemoveAtIndex(head, 0);
    return head;
}

node* DReverse(node* head)
{
    return LReverse(head, 0);
}

node* DShiftLeft(node* head)
{
    node* last_node = LGetNode(head, LSize(head) - 1);
    last_node->next = head;
    head = head->next;
    last_node->next->next = 0;
    return head;
}

node* DShiftRight(node* head)
{
    node* second_last_node = LGetNode(head, LSize(head) - 2);
    second_last_node->next->next = head;
    head = second_last_node->next;
    second_last_node->next = 0;
    return head;
}

node* DSort(node* head)
{
    return LSort(head);
}

void DPrintStartAdress(node* head)
{
    printf("Startadress: %p\n", &head);
}