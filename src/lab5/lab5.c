#include <stdio.h>
#include <limits.h>
#include <locale.h>

#define V 9
#define E 18
#define INF INT_MAX

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

void initEdges(Edge edges[]) {
    edges[0] = (Edge){ 9, 1, 3 };
    edges[1] = (Edge){ 1, 2, 5 };
    edges[2] = (Edge){ 1, 6, 19 };
    edges[3] = (Edge){ 1, 7, 3 };
    edges[4] = (Edge){ 1, 4, 6 };
    edges[5] = (Edge){ 2, 3, 5 };
    edges[6] = (Edge){ 2, 7, 3 };
    edges[7] = (Edge){ 2, 5, 4 };
    edges[8] = (Edge){ 3, 9, 6 };
    edges[9] = (Edge){ 3, 3, 5 };
    edges[10] = (Edge){ 3, 5, 1 };
    edges[11] = (Edge){ 4, 6, 9 };
    edges[12] = (Edge){ 4, 7, 1 };
    edges[13] = (Edge){ 5, 3, 2 };
    edges[14] = (Edge){ 6, 9, 1 };
    edges[15] = (Edge){ 6, 7, 4 };
    edges[16] = (Edge){ 7, 5, 4 };
    edges[17] = (Edge){ 3, 2, 2 };
}
void buildAdjMatrix(Edge edges[], int matrix[V][V], int numEdges) {
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            matrix[i][j] = (i == j) ? 0 : INF;
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].from - 1;
        int v = edges[i].to - 1;
        matrix[u][v] = edges[i].weight;
    }
}

void diikstra(int matrix[V][V], int start, int target) {
    int dist[V], visited[V] = { 0 }, parent[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;
    for (int i = 0; i < V - 1; i++) {
        int u = -1;
        for (int j = 0; j < V; j++)
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        if (u == -1) break;
        visited[u] = 1;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && matrix[u][v] != INF &&
                dist[u] + matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + matrix[u][v];
                parent[v] = u;
            }
        }
    }
    printf("Дейкстра: путь из %d в %d: ", start + 1, target + 1);
    if (dist[target] == INF) {
        printf("пути нет\n");
        return;
    }
    int path[V], k = 0;
    for (int v = target; v != -1; v = parent[v])
        path[k++] = v;
    for (int i = k - 1; i >= 0; i--)
        printf("%d ", path[i] + 1);
    printf("\nДлина пути: %d\n\n", dist[target]);
}

void Gfloyd(int matrix[V][V], int start, int target) {
    int dist[V][V], next[V][V];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) {
            dist[i][j] = matrix[i][j];
            next[i][j] = (matrix[i][j] != INF && i != j) ? j : -1;
        }
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
    printf("Флойд–Уоршелл: путь из %d в %d: ", start + 1, target + 1);
    if (next[start][target] == -1) {
        printf("пути нет\n");
        return;
    }
    int u = start;
    while (u != target) {
        printf("%d ", u + 1);
        u = next[u][target];
    }
    printf("%d\nДлина пути: %d\n", target + 1, dist[start][target]);
}

int lab5_main() {
    setlocale(LC_ALL, "Russian");
    Edge edges[E];
    initEdges(edges);
    int adjMatrix[V][V];
    buildAdjMatrix(edges, adjMatrix, E);
    diikstra(adjMatrix, 3, 0);
    Gfloyd(adjMatrix, 3, 0);
    return 0;
}
