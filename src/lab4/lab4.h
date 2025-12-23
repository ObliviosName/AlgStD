#ifndef LAB4_H
#define LAB4_H

#include <stdio.h>

struct Node {
    char* key;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(const char* word);
struct Node* insert(struct Node* root, const char* word);
struct Node* findMin(struct Node* root);
struct Node* deleteByLength(struct Node* root, int len);
void freeTree(struct Node* root);

/* printTree объявлен, но реализован В ЭТОЙ ЖЕ lab4.c */
struct Trunk;
void printTree(struct Node* root, struct Trunk* prev, int isLeft);

int lab4_main(void);

#endif
