#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>



struct Node {
    char* key;
    struct Node* left;
    struct Node* right;
};



struct Node* createNode(const char* word) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->key = _strdup(word);   // Windows-safe version of strdup
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct Node* insert(struct Node* root, const char* word) {
    if (!root) return createNode(word);

    if (strcmp(word, root->key) < 0)
        root->left = insert(root->left, word);
    else if (strcmp(word, root->key) > 0)
        root->right = insert(root->right, word);

    return root;
}

/* ------------------
   DELETE by WORD LENGTH
   ------------------ */

struct Node* findMin(struct Node* root) {
    while (root->left) root = root->left;
    return root;
}

struct Node* deleteByLength(struct Node* root, int len) {
    if (!root) return NULL;

    root->left = deleteByLength(root->left, len);
    root->right = deleteByLength(root->right, len);

    if ((int)strlen(root->key) == len) {
        // delete this node
        if (!root->left) {
            struct Node* r = root->right;
            free(root->key);
            free(root);
            return r;
        }
        else if (!root->right) {
            struct Node* l = root->left;
            free(root->key);
            free(root);
            return l;
        }
        else {
            struct Node* m = findMin(root->right);
            free(root->key);
            root->key = _strdup(m->key);
            root->right = deleteByLength(root->right, (int)strlen(m->key));
        }
    }

    return root;
}

/* ------------------
   FREE TREE
   ------------------ */
void freeTree(struct Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root->key);
    free(root);
}

/* ------------------
   Prototype for printTree
   ------------------ */
struct Trunk;
void printTree(struct Node* root, struct Trunk* prev, int isLeft);

/* ------------------
          MAIN
   ------------------ */

int lab4_main() {
    setlocale(LC_ALL, "");

    struct Node* root = NULL;

    FILE* f = fopen("input.txt", "r");
    if (!f) {
        printf("Не удалось открыть input.txt\n");
        return 1;
    }

    char word[256];

    while (fscanf(f, "%255s", word) == 1) {
        root = insert(root, word);
    }
    fclose(f);

    printf("Дерево, построенное по словам из файла:\n\n");
    printTree(root, NULL, 0);

    int L;
    printf("\nВведите длину слова для удаления: ");
    scanf("%d", &L);

    root = deleteByLength(root, L);

    printf("\nДерево после удаления слов длины %d:\n\n", L);
    printTree(root, NULL, 0);

    freeTree(root);

    return 0;
}
