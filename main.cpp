#include <iostream>
#include <cstdio>
#include "conio21/conio2.h"
#include "appconsts.h"
#include "interface.h"

const int INFINITY = 10000000;
const int MAIN_DIAG_MARK = -1000000;

#define min(x, y) (x < y) ? x : y


void prepareMatrix(float** graph, int pointsCount) {
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            if (i == j) graph[i][j] = MAIN_DIAG_MARK;
            else if (graph[i][j] == 0) graph[i][j] = INFINITY;
        }
    }
}

void floydAlgorithm(float** graph, int pointsCount) {
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

}

void inputGraphMatrix(float** graph, int pointsCount) {
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            if (i == j) {
                printf("[  X  ]"); graph[i][j] = MAIN_DIAG_MARK;
            }
            else {
                printf("[     ]"); gotoxy(7*j + 2, i + 2);
                scanf("%f", &graph[i][j]);
                if (j == pointsCount) {
                    gotoxy(7*(j+1) + 1, i + 2);
                }
                else {
                    gotoxy(1, i + 3);
                }
                putchar(8); putchar(8); putchar(8);//printf("\b ");
            }
        }
    }
}

int main() {
    setWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
    drawFrame(64, 30, 2, 2);
    setCP(1251);
    int choice = 1;
    do {
        choice = drawMenu(choice, mainMenu, 4, 5, 12, 4, 2, 1);
        switch (choice) {
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {

                break;
            }
            default: {
                return 0;
            }
        }
    } while (choice != 4);
    /*int pointsCount; scanf("%d", &pointsCount);
    float** adjustmentMatrix = new float*[pointsCount];
    for (int i = 0; i < pointsCount; i++) {
        adjustmentMatrix[i] = new float [pointsCount];
        //for (int j = 0; j < pointsCount; j++) scanf("%f", &adjustmentMatrix[i][j]);
    }
    inputGraphMatrix(adjustmentMatrix, pointsCount);
    floydAlgorithm(adjustmentMatrix, pointsCount);
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            if (adjustmentMatrix[i][j] == INFINITY) {
                printf("INF ");
            }
            else if (adjustmentMatrix[i][j] == MAIN_DIAG_MARK) {
                printf("X ");
            }
            else {
                printf("%f ", adjustmentMatrix[i][j]);
            }

        }
        printf("\n");
    }
    getchar(); getchar(); getchar(); getchar(); getchar();*/
    //std::cout << "Hello, World!" << std::endl;
    //return 0;
}
