#include <windows.h>
#include <cstdio>
#include "conio21/conio2.h"

#define max(x, y) ((x > y) ? x : y)
#define setCP(cpCode) SetConsoleCP(cpCode); SetConsoleOutputCP(cpCode)
#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

const char CP866_FRAME_HORIZONTAL = 0xCD;
const char CP886_FRAME_VERTICAL = 0xBA;
const char CP886_FRAME_CORNER_LEFT_TOP = 0xC9;
const char CP886_FRAME_CORNER_LEFT_BOTTOM = 0xC8;
const char CP886_FRAME_CORNER_RIGHT_TOP = 0xBB;
const char CP886_FRAME_CORNER_RIGHT_BOTTOM = 0xBC;



void waitForKey(int code) {
    int key;
    do key = getch(); while (key != code);
    while(kbhit() != 0) key = getch();
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


void setWindowSize(int columns, int lines) {
    char sysSWS[64];
    sprintf(sysSWS, "mode con cols=%d lines=%d", columns, lines);
    system(sysSWS);
}

void drawFrame(int width, int height, int drawX, int drawY) {
    gotoxy(drawX, drawY);
    char* topBorder = new char[width + 1];
    char* bottomBorder = new char[width + 1];
    char* rlBorder = new char[width + 1];
    topBorder[0] = CP886_FRAME_CORNER_LEFT_TOP; bottomBorder[0] = CP886_FRAME_CORNER_LEFT_BOTTOM; rlBorder[0] = CP886_FRAME_VERTICAL;
    topBorder[width - 1] = CP886_FRAME_CORNER_RIGHT_TOP; bottomBorder[width - 1] = CP886_FRAME_CORNER_RIGHT_BOTTOM; rlBorder[width - 1] = CP886_FRAME_VERTICAL;
    topBorder[width] = 0; bottomBorder[width] = 0; rlBorder[width] = 0;
    for (int i = 1; i < width - 1; i++) {
        topBorder[i] = CP866_FRAME_HORIZONTAL; bottomBorder[i] = CP866_FRAME_HORIZONTAL; rlBorder[i] = ' ';
    }
    setCP(866);
    printf(topBorder);
    for (int i = 0; i < height - 2; i++) {
        gotoxy(drawX, drawY + i + 1);
        printf(rlBorder);
    }
    gotoxy(drawX, drawY + height - 1);
    printf(bottomBorder);
    setCP(1251);
}


int drawMenu(
        int activePos,
        char* menuPoints[],
        int pointsCount,
        int drawX,
        int drawY,
        int alignCenterH,
        int alignCenterV,
        short activePointColor
) {
    int key;
    gotoxy(drawX, drawY);
    int maxLen = -1;
    for (int i = 0; i < pointsCount; i++) maxLen = max(maxLen, (int) strlen(menuPoints[i]));

    drawFrame(maxLen + alignCenterH*2 + 2, pointsCount + alignCenterV * 2 + 2, drawX, drawY);
    for (int i = 0; i < pointsCount; i++) {
        gotoxy(drawX + alignCenterH + 1, drawY + alignCenterV + 1 + i);
        printf(menuPoints[i]);
    }
    textbackground(activePointColor);
    gotoxy(drawX + alignCenterH + 1, drawY + alignCenterV + activePos);
    printf(menuPoints[activePos - 1]);
    do {
        key = getch();
        if (key != 13) {
            textbackground(0);
            gotoxy(drawX + alignCenterH + 1, drawY + alignCenterV + activePos);
            printf(menuPoints[activePos - 1]);
            if (key == 224) {
                key = getch();
                if (key == 80) {
                    if (activePos == pointsCount) activePos = 1;
                    else activePos += 1;
                }
                else if (key == 72) {
                    if (activePos == 1) activePos = pointsCount;
                    else activePos -= 1;
                }
            }
            textbackground(activePointColor);
            gotoxy(drawX + alignCenterH + 1, drawY + alignCenterV + activePos);
            printf(menuPoints[activePos - 1]);
        }
    } while (key != 13);
    while (kbhit() != 0) getch();
    textbackground(0);
    return activePos;
}
#endif // INTERFACE_H_INCLUDED
