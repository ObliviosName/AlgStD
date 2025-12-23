#ifndef LAB5_H
#define LAB5_H

#include <stdio.h>

#define V 9
#define E 18

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

void initEdges(Edge edges[]);
void buildAdjMatrix(Edge edges[], int matrix[V][V], int numEdges);
void diikstra(int matrix[V][V], int start, int target);
void Gfloyd(int matrix[V][V], int start, int target);

int lab5_main(void);

#endif
