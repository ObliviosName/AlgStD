#ifndef LAB3_H
#define LAB3_H

#include <stdio.h>

typedef struct Node {
    double value;
    struct Node* next;
} Node;

Node* createNode(double value);
void append(Node** head, double value);
void printList(Node* head);
double sumList(Node* head);
Node* find(Node* head);
void freeList(Node* head);

int lab3_main(void);

#endif
