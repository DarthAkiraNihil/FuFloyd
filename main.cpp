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
    fprintf(file, (afterFloyd) ? "�������, ����� ���������� ��������� ������\n" : "������� ������� ��������� �����:\n");
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
                    gotoxy(4, 4); printf("������� ���������� ������ � ����� (����. 8): ");
                    scanf("%d", &pointsCount);
                    if (pointsCount < 1 || pointsCount > 8) {
                        gotoxy(4, 5); printf("������� ������� ���������� ������ �����.\n");
                        gotoxy(4, 6); printf("����������, ���������� ��� ���.\n");
                        gotoxy(4, 7); printf("������� ����� ������� ��� �����������");
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
                gotoxy(4, 5); printf("��������� � ���������� ������� ������� �����");
                for (int i = 0; i < pointsCount; i++) {
                    for (int j = 0; j < pointsCount; j++) {
                        gotoxy(4, 6 + j);
                        printf("������� ������� V[%d][%d]: ", i + 1, j + 1);
                        //gotoxy(29, 6 + j);
                        if (i == j) {
                            printf("[������� ������� ���������]");
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
                gotoxy(4, 5); printf("������� ������� ����� ������� ���������.    "); getchar();
                int outputMode;
                gotoxy(4, 6); printf("���� ������� �������� �������?");
                do {
                    gotoxy(4, 7); printf("1 - � ���� (���������� �������� ������), 2 - � �������: ");
                    scanf("%d", &outputMode);
                    if (outputMode != 1 && outputMode != 2) {
                        gotoxy(4, 8); printf("������� ����� ����� ������\n");
                        gotoxy(4, 9); printf("����������, ���������� ��� ���.\n");
                        gotoxy(4, 10); printf("������� ����� ������� ��� �����������");
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
                        gotoxy(4, 6); printf("������� ������ �������� � ���� %s", outputFile);
                        gotoxy(4, 7); printf("������� ����� ������� ��� �����������");
                        waitForKey(13);
                        fclose(out);
                        break;
                    }
                    case 2: {
                        int stepByStep;
                        do {
                            gotoxy(4, 6); printf("��������� �������� ��������? (1 - ��, 0 - ���) ");
                            scanf("%d", &stepByStep);
                            if (stepByStep != 1 && stepByStep != 0) {
                                gotoxy(4, 7); printf("������� ����� ����� ����������� ����������\n");
                                gotoxy(4, 8); printf("����������, ���������� ��� ���.\n");
                                gotoxy(4, 9); printf("������� ����� ������� ��� �����������");
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
                                gotoxy(4, 6); printf("���������� ��������� ������ ��������");
                                for (int k = 0; k < pointsCount; k++) {
                                    floydAlgorithmOneStep(adjacencyMatrix, pointsCount, k);
                                    gotoxy(4, 7); printf("�������� %d/%d", k + 1, pointsCount);
                                    printAdjacencyMatrix(adjacencyMatrix, pointsCount, 4, 9);
                                    gotoxy(4, 10 + pointsCount); printf("Enter = ��������� ��������");
                                    waitForKey(13);
                                }
                                gotoxy(4, 7); printf("�������, ����� ���������� ��������� ������:");
                                gotoxy(4, 10 + pointsCount); printf("������� Enter ��� �����������");
                                waitForKey(13);
                                break;
                            }
                            case 0: {
                                floydAlgorithm(adjacencyMatrix, pointsCount);
                                gotoxy(4, 7); printf("�������, ����� ���������� ��������� ������:");
                                printAdjacencyMatrix(adjacencyMatrix, pointsCount, 4, 9);
                                gotoxy(4, 10 + pointsCount); printf("������� Enter ��� �����������");
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
                gotoxy(4, 4); printf("������� ��� ����� �����: ");
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
                    gotoxy(4, 5); printf("������� ������ �������� � ���� %s", outputFile);
                    gotoxy(4, 6); printf("������� Enter ��� �����������");
                    waitForKey(13);
                    fclose(out);
                    fclose(out);
                    for (int i = 0; i < pointsCount; i++) delete [] adjacencyMatrix[i];
                    delete [] adjacencyMatrix;
                }
                else {
                    gotoxy(4, 5); printf("������ ����� �� ����������");
                    gotoxy(4, 6); printf("������� Enter ��� �����������");
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
