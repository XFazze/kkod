#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "node.h"

int LSize(node* head)
{
    int size = 0;
    node* cnode = head;
    while (cnode != 0)
    {
        size++;
        cnode = cnode->next;
    }
    return size;
}

int LIsEmpty(node* head)
{
    if (head == 0)
        return 1;
    else
        return 0;
}

node* LGetNode(node* head, int index)
{
    node* cnode = head;
    for (int i = 0; i < index; i++)
    {
        cnode = cnode->next;
    }
    return cnode;
}

int LContains(node* head, int value)
{
    node* cnode = head;
    while (cnode != 0)
    {
        if (cnode->el == value)
            return 1;
        cnode = cnode->next;
    }
    return 0;
}

int LGetFirstIndexOf(node* head, int value)
{
    node* cnode = head;
    int index = 0;
    while (cnode != 0)
    {
        if (cnode->el == value)
            return index;
        cnode = cnode->next;
        index++;
    }
    return -1;
}

node* LInsertElement(node* head, int value, int index)
{
    node* new_node = malloc(sizeof(node));
    new_node->el = value;
    if (head == 0)
    {
        new_node->next = 0;
        head = new_node;
        return head;
    }
    if (index == 0)
    {
        new_node->next = head;

        head = new_node;
        return head;
    }
    node* previousNode = LGetNode(head, index - 1);
    new_node->next = previousNode->next;
    previousNode->next = new_node;
    return head;
}

node* LRemoveAtIndex(node* head, int index)
{
    if (index == 0)
    {
        if (head->next != 0)
        {
            node* new_head = head->next;
            free(head);
            return new_head;
        }
        else
        {
            free(head);
            return 0;
        }
    }
    node* previousNode = LGetNode(head, index - 1);
    node* nextNode = LGetNode(head, index + 1);
    free(previousNode->next);
    previousNode->next = nextNode;
    return head;
}

node* LSort(node* head)
{
    int no_change;
    node* cnode;
    do
    {
        no_change = 1;
        cnode = head;
        if (head->el > head->next->el)
        {
            head = head->next;
            cnode->next = head->next;
            head->next = cnode;
        }
        cnode = head;
        // cnode + 1 vs cnode + 2
        while (cnode->next->next != 0)
        {
            if (cnode->next->el > cnode->next->next->el)
            {
                node* old_first = cnode->next;
                cnode->next = cnode->next->next;
                old_first->next = cnode->next->next;
                cnode->next->next = old_first;
                no_change = 0;
            }
            cnode = cnode->next;
        }
    } while (no_change == 0);
    return head;
}

node* LGetNext(node* cnode)
{
    return cnode->next;
}

int LGetValue(node* cnode)
{
    return cnode->el;
}

node* LReverse(node* cnode, int depth)
{
    if (cnode->next == 0)
        return cnode;
    node* last_node = LReverse(cnode->next, depth + 1);
    cnode->next->next = cnode;
    if (depth == 0)
        cnode->next = 0;
    return last_node;
}