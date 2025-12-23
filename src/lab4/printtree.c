#include "lab4.h"
#include <stdlib.h>

void showTrunks(struct Trunk* p) {
    if (p == NULL) return;

    showTrunks(p->prev);
    printf("%s", p->str);
}

void printTree(struct AVLNode* root, struct Trunk* prev, int isLeft) {
    if (root == NULL) return;
    //cout << endl;

    char* prev_str = "     ";

    struct Trunk* trunk = (struct Trunk*)malloc(sizeof(struct Trunk));   //new Trunk;   // (prev, prev_str);
    trunk->prev = prev;
    trunk->str = prev_str;

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "-----";
    }
    else if (isLeft) {
        trunk->str = ".----";
        prev_str = "    |";
    }
    else {
        trunk->str = "`----";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    //cout << " " << root->data << endl;
    printf(" %d\n", root->key);

    if (prev) prev->str = prev_str;
    trunk->str = "    |";

    printTree(root->left, trunk, false);
    free(trunk);
}
