#include <iostream>
#include <cstdio>

const int INFINITY = 10000000;
const int MAIN_DIAG_MARK = -1000000;

#define min(x, y) (x < y) ? x : y

void prepareMatrix(int** graph, int pointsCount) {
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            if (i == j) graph[i][j] = MAIN_DIAG_MARK;
            else if (graph[i][j] == 0) graph[i][j] = INFINITY;
        }
    }
}

void floydAlgorithm(int** graph, int pointsCount) {
    prepareMatrix(graph, pointsCount);
    for (int k = 0; k < pointsCount; k++) {
        for (int i = 0; i < pointsCount; i++) {
            for (int j = 0; j < pointsCount; j++) {
                if (graph[i][k] != INFINITY && graph[k][j] != INFINITY && i != k && j != k) {
                    if (graph[i][j] == INFINITY) {
                        graph[i][j] = graph[i][k] + graph[k][j];
                    }
                    else graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }


            }
        }
    }
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            if (graph[i][j] == INFINITY) {
                printf("INF ");
            }
            else if (graph[i][j] == MAIN_DIAG_MARK) {
                printf("X ");
            }
            else {
                printf("%d ", graph[i][j]);
            }

        }
        printf("\n");
    }
}


int main() {

    int pointsCount; scanf("%d", &pointsCount);
    int** adjustmentMatrix = new int*[pointsCount];
    for (int i = 0; i < pointsCount; i++) {
        adjustmentMatrix[i] = new int[pointsCount];
        for (int j = 0; j < pointsCount; j++) scanf("%d", &adjustmentMatrix[i][j]);
    }
    floydAlgorithm(adjustmentMatrix, pointsCount);
    getchar(); getchar(); getchar(); getchar(); getchar();
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
