#include <cctype>
#include <memory.h>
#include <ctime>
#include <cstring>
#include <cstdio>
#include "conio21/conio2.h"
#include "appconsts.h"
#include "interface.h"

const int INFINITY = 10000000;
const int MAIN_DIAG_MARK = -1000000;

#define min(x, y) (x < y) ? x : y
#define DrawMainFrame drawFrame(78, 30, 2, 2)
#define PrintNullLine printf("                                                           ")

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

void printAdjacencyMatrix(float** graph, int pointsCount, int ltcX, int ltcY) {
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            gotoxy(ltcX + j * 7, ltcY + i);
            if (graph[i][j] == INFINITY) {
                printf("[ INF ]");
            }
            else if (graph[i][j] == MAIN_DIAG_MARK) {
                printf("[  X  ]");
            }
            else {
                printf("[%5.2f]", graph[i][j]);
                /*printf("[");
                printf("%5.2f", graph[i][j]);
                gotoxy(ltcX + j * 7 + 6, ltcY + i); printf("]");*/
            }
        }
    }
}

void writeAdjacencyMatrixToFile(float** graph, int pointsCount, FILE* file, bool afterFloyd = false) {
    fprintf(file, (afterFloyd) ? "Матрица, после применения алгоритма Флойда\n" : "Весовая матрица введённого графа:\n");
    for (int i = 0; i < pointsCount; i++) {
        for (int j = 0; j < pointsCount; j++) {
            if (graph[i][j] == INFINITY) {
                fprintf(file, "[   INF   ]");
            }
            else if (graph[i][j] == MAIN_DIAG_MARK) {
                fprintf(file, "[    X    ]");
            }
            else {
                fprintf(file, "[%9.3f]", graph[i][j]);
            }
        }
        fprintf(file, "\n");

    }
    fprintf(file, "\n");
}

int main() {
    setWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
    hideCursor();
    drawFrame(78, 30, 2, 2);
    setCP(1251);
    float** adjacencyMatrix;
    int choice = 1;
    do {
        DrawMainFrame;
        choice = drawMenu(choice, mainMenu, 4, 5, 12, 4, 2, 1);
        switch (choice) {
            case 1: {
                DrawMainFrame;
                int pointsCount = 0;
                do {
                    gotoxy(4, 4); printf("Введите количество вершин в графе (маск. 8): ");
                    scanf("%d", &pointsCount);
                    if (pointsCount < 1 || pointsCount > 8) {
                        gotoxy(4, 5); printf("Неверно введено количество вершин графа.\n");
                        gotoxy(4, 6); printf("Пожалуйста, попробуйте ещё раз.\n");
                        gotoxy(4, 7); printf("Нажмите любую клавишу для продолжения");
                        getchar(); getchar();
                        gotoxy(4, 5); PrintNullLine;
                        gotoxy(4, 6); PrintNullLine;
                        gotoxy(4, 7); PrintNullLine;
                        gotoxy(4, 4); PrintNullLine;
                    }
                } while (pointsCount < 1 || pointsCount > 8);
                adjacencyMatrix = new float* [pointsCount];
                for (int i = 0; i < pointsCount; i++) {
                    adjacencyMatrix[i] = new float [pointsCount];
                }
                gotoxy(4, 5); printf("Переходим к заполнению весовой матрицы графа");
                for (int i = 0; i < pointsCount; i++) {
                    for (int j = 0; j < pointsCount; j++) {
                        gotoxy(4, 6 + j);
                        printf("Введите элемент V[%d][%d]: ", i + 1, j + 1);
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
                gotoxy(4, 5); printf("Весовая матрица графа успешно заполнена.    "); getchar();
                int outputMode;
                gotoxy(4, 6); printf("Куда вывести итоговую матрицу?");
                do {
                    gotoxy(4, 7); printf("1 - в файл (повышенная точность вывода), 2 - в консоли: ");
                    scanf("%d", &outputMode);
                    if (outputMode != 1 && outputMode != 2) {
                        gotoxy(4, 8); printf("Неверно введён режим вывода\n");
                        gotoxy(4, 9); printf("Пожалуйста, попробуйте ещё раз.\n");
                        gotoxy(4, 10); printf("Нажмите любую клавишу для продолжения");
                        waitForKey(13);
                        //getchar(); getchar();
                        gotoxy(4, 8); PrintNullLine;
                        gotoxy(4, 9); PrintNullLine;
                        gotoxy(4, 10); PrintNullLine;
                        gotoxy(4, 7); PrintNullLine;
                    }
                } while (outputMode != 1 && outputMode != 2);
                gotoxy(4, 6); PrintNullLine;
                gotoxy(4, 7); PrintNullLine;
                switch (outputMode) {
                    case 1: {
                        time_t sc = time(nullptr);
                        char outputFile[255]; sprintf(outputFile, "graph-%lld.txt", (long long) sc);
                        outputFile[strlen(outputFile)] = 0;
                        FILE* out = fopen(outputFile, "w+");
                        writeAdjacencyMatrixToFile(adjacencyMatrix, pointsCount, out);
                        floydAlgorithm(adjacencyMatrix, pointsCount);
                        writeAdjacencyMatrixToFile(adjacencyMatrix, pointsCount, out, true);
                        gotoxy(4, 6); printf("Матрица Флойда записана в файл %s", outputFile);
                        gotoxy(4, 7); printf("Нажмите любую клавишу для продолжения");
                        waitForKey(13);
                        fclose(out);
                        break;
                    }
                    case 2: {
                        int stepByStep;
                        do {
                            gotoxy(4, 6); printf("Выполнять алгоритм пошагово? (1 - да, 0 - нет) ");
                            scanf("%d", &stepByStep);
                            if (stepByStep != 1 && stepByStep != 0) {
                                gotoxy(4, 7); printf("Неверно введён режим отображения выполнения\n");
                                gotoxy(4, 8); printf("Пожалуйста, попробуйте ещё раз.\n");
                                gotoxy(4, 9); printf("Нажмите любую клавишу для продолжения");
                                waitForKey(13);
                                gotoxy(4, 7); PrintNullLine;
                                gotoxy(4, 8); PrintNullLine;
                                gotoxy(4, 9); PrintNullLine;
                                gotoxy(4, 6); PrintNullLine;
                            }
                            gotoxy(4, 6); PrintNullLine;
                        } while(stepByStep != 1 && stepByStep != 0);
                        switch (stepByStep) {
                            case 1: {
                                prepareMatrix(adjacencyMatrix, pointsCount);
                                gotoxy(4, 6); printf("Выполнение алгоритма Флойда пошагово");
                                for (int k = 0; k < pointsCount; k++) {
                                    floydAlgorithmOneStep(adjacencyMatrix, pointsCount, k);
                                    gotoxy(4, 7); printf("Итерация %d/%d", k + 1, pointsCount);
                                    printAdjacencyMatrix(adjacencyMatrix, pointsCount, 4, 9);
                                    gotoxy(4, 10 + pointsCount); printf("Enter = Следующая итерация");
                                    waitForKey(13);
                                }
                                gotoxy(4, 7); printf("Матрица, после выполнения алгоритма Флойда:");
                                gotoxy(4, 10 + pointsCount); printf("Нажмите Enter для продолжения");
                                waitForKey(13);
                                break;
                            }
                            case 0: {
                                floydAlgorithm(adjacencyMatrix, pointsCount);
                                gotoxy(4, 7); printf("Матрица, после выполнения алгоритма Флойда:");
                                printAdjacencyMatrix(adjacencyMatrix, pointsCount, 4, 9);
                                gotoxy(4, 10 + pointsCount); printf("Нажмите Enter для продолжения");
                                waitForKey(13);
                                break;
                            }
                        }
                        break;
                    }
                }
                for (int i = 0; i < pointsCount; i++) delete [] adjacencyMatrix[i];
                delete [] adjacencyMatrix;
                break;
            }
            case 2: {
                DrawMainFrame;
                int pointsCount = 0;
                char graphFileName[255];
                gotoxy(4, 4); printf("Введите имя файла графа: ");
                fgets(graphFileName, 255, stdin);
                graphFileName[strlen(graphFileName) - 1] = 0;
                FILE* graphFile = fopen(graphFileName, "r");
                if (graphFile != nullptr) {
                    fscanf(graphFile, "%d", &pointsCount);
                    adjacencyMatrix = new float* [pointsCount];
                    for (int i = 0; i < pointsCount; i++) {
                        adjacencyMatrix[i] = new float [pointsCount];
                    }
                    char line[512]; line[0] = 0;
                    fgets(line, 512, graphFile);
                    for (int i = 0; i < pointsCount; i++) {
                        int index = 0;
                        fgets(line, 512, graphFile);
                        char * tokenPointer = strtok(line, " ");
                        while (tokenPointer != nullptr) {
                            adjacencyMatrix[i][index++] = (float) atof(tokenPointer);
                            tokenPointer = strtok(nullptr, " ");
                        }
                    }

                    time_t sc = time(nullptr);
                    char outputFile[255]; sprintf(outputFile, "graph-%lld.txt", (long long) sc);
                    outputFile[strlen(outputFile)] = 0;
                    FILE* out = fopen(outputFile, "w+");

                    writeAdjacencyMatrixToFile(adjacencyMatrix, pointsCount, out);
                    floydAlgorithm(adjacencyMatrix, pointsCount);
                    writeAdjacencyMatrixToFile(adjacencyMatrix, pointsCount, out, true);
                    gotoxy(4, 5); printf("Матрица Флойда записана в файл %s", outputFile);
                    gotoxy(4, 6); printf("Нажмите Enter для продолжения");
                    waitForKey(13);
                    fclose(out);
                    fclose(out);
                    for (int i = 0; i < pointsCount; i++) delete [] adjacencyMatrix[i];
                    delete [] adjacencyMatrix;
                }
                else {
                    gotoxy(4, 5); printf("Такого файла не существует");
                    gotoxy(4, 6); printf("Нажмите Enter для продолжения");
                    waitForKey(13);
                }
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
}
