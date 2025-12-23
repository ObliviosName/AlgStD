#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    double value;
    struct Node* next;
} Node;

Node* createNode(double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("error\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, double value) {
    Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* cur = *head;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = newNode;
}

void printList(Node* head) {
    if (!head) {
        printf("List empty.\n");
        return;
    }
    Node* cur = head;
    printf("List: ");
    while (cur) {
        printf("%.2lf ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}

double sumList(Node* head) {
    double sum = 0;
    Node* cur = head;
    while (cur) {
        sum += cur->value;
        cur = cur->next;
    }
    return sum;
}

Node* find(Node* head) {
    double total = sumList(head);
    Node* cur = head;
    while (cur) {
        double others = total - cur->value;
        if (cur->value > others)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

void freeList(Node* head) {
    Node* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int lab3_main() {
    Node* head = NULL;
    int ch;
    double val;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Add\n");
        printf("2. Check\n");
        printf("3. Exit\n");
        printf(">> ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            printf("Val: ");
            scanf("%lf", &val);
            append(&head, val);
            printList(head);
            break;
        case 2: {
            if (!head) {
                printf("Empty\n");
                break;
            }
            Node* res = find(head);
            if (res)
                printf("Krutoe chislo: %.2lf\n", res->value);
            else
                printf("No.\n");
            break;
        }
        case 3:
            freeList(head);
            printf("Byyyyye\n");
            break;
        default:
            printf(":(\n");
        }
    } while (ch != 3);

    return 0;
}
