#include <memory.h>
#include <cstdio>
#include "conio21/conio2.h"
#include "appconsts.h"
#include "interface.h"

const int INFINITY = 10000000;
const int MAIN_DIAG_MARK = -1000000;

#define min(x, y) (x < y) ? x : y
#define DrawMainFrame drawFrame(78, 30, 2, 2)
#define PrintNullLine printf("                                                       ")

void prepareMatrix(float** graph, int pointsCount) {
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            if (i == j) graph[i][j] = MAIN_DIAG_MARK;
            else if (graph[i][j] == 0) graph[i][j] = INFINITY;
        }
    }
}

void floydAlgorithmOneStep(float** graph, int pointsCount, int iteration) {
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            if (graph[i][iteration] != INFINITY && graph[iteration][j] != INFINITY && i != iteration && j != iteration) {
                if (graph[i][j] == INFINITY) {
                    graph[i][j] = graph[i][iteration] + graph[iteration][j];
                }
                else graph[i][j] = min(graph[i][j], graph[i][iteration] + graph[iteration][j]);
            }
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

void makeNullMatrix(float** graph, int pointsCount) {
    graph = new float* [pointsCount];
    for (int i = 0; i < pointsCount; i++) {
        graph[i] = new float[pointsCount];
        //memset(graph[i], 0, pointsCount * sizeof(float));
    }
}

void inputMatrix() {
    //makeNullMatrix(graph, pointsCount);
    DrawMainFrame;

    int pointsCount = 0;
    do {
        gotoxy(4, 4); printf("Введите количество вершин в графе (маск. 8): ");
        scanf("%d", &pointsCount);
        if (pointsCount < 1 || pointsCount > 8) {
            printf("Неверно введено количество вершин графа.\n");
            printf("Пожалуйста, попробуйте ещё раз.\n");
            printf("Нажмите любую клавишу для продолжения");
            getchar();
            gotoxy(4, 5); PrintNullLine;
            gotoxy(4, 6); PrintNullLine;
            gotoxy(4, 7); PrintNullLine;
        }
    } while (pointsCount < 1 || pointsCount > 8);
    //makeNullMatrix(graph, pointsCount)
    // ;
    float** adjacencyMatrix = new float* [pointsCount];
    for (int i = 0; i < pointsCount; i++) {
        adjacencyMatrix[i] = new float [pointsCount];
    }
    gotoxy(4, 5); printf("Переходим к заполнению матрицы смежности графа");
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            gotoxy(4, 6 + j);
            printf("Введите элемент A[%d][%d]: ", i + 1, j + 1);
            //gotoxy(29, 6 + j);
            if (i == j) {
                printf("[ЭЛЕМЕНТ ГЛАВНОЙ ДИАГОНАЛИ]");
                adjacencyMatrix[i][j] = MAIN_DIAG_MARK;
            }
            else {
                scanf("%f", &adjacencyMatrix[i][j]);
            }
        }
        for (int j = 0; j < pointsCount; j++) {
            gotoxy(4, 6 + j); PrintNullLine;
        }
    }
    printf("%.2f", adjacencyMatrix[0][1]);

    for (int i = 0; i < pointsCount; i++) delete [] adjacencyMatrix[i];
    delete [] adjacencyMatrix;
}

int main() {
    setWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
    hideCursor();
    drawFrame(78, 30, 2, 2);

    setCP(1251);
    float** adjacencyMatrix;
    int choice = 1;
    do {
        choice = drawMenu(choice, mainMenu, 4, 5, 12, 4, 2, 1);
        switch (choice) {
            case 1: {
                inputMatrix();
                //printf("%f", adjacencyMatrix[0][1]);
                //getchar();

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
