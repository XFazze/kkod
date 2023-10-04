#ifndef NODE_H
#define NODE_H

struct Node {
    int el;
    struct Node* next;
};

typedef struct Node node;

#endif