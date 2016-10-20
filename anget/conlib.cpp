#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "conlib.h"

void gotoxy(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)x, (short)y });
}

int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbi);
    return sbi.dwCursorPosition.X;
}

int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbi);
    return sbi.dwCursorPosition.Y;
}

void setCursorType(CursorType c)
{
    CONSOLE_CURSOR_INFO CurInfo;

    switch (c)
    {
        case CursorType::No:
            CurInfo.dwSize = 1;
            CurInfo.bVisible = FALSE;
            break;
        case CursorType::Solid:
            CurInfo.dwSize = 100;
            CurInfo.bVisible = TRUE;
            break;
        case CursorType::Normal:
            CurInfo.dwSize = 20;
            CurInfo.bVisible = TRUE;
            break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void consize(int width, int height)
{
    char buf[256];
    snprintf(buf, sizeof(buf), "mode con cols=%d lines=%d", width, height);
    system(buf);
}

void clrscr()
{
    system("cls");
}

void delay(int ms)
{
    Sleep(ms);
}

int getkey()
{
    int ch = _getch();
    if (ch == 0 || ch == 0xe0)
        ch = 0x1000 | _getch();
    return toupper(ch);
}

unsigned gettick()
{
    return GetTickCount();
}

void printbar(int value, int max, int size, char full, char half, char empty)
{
    int ext_val = value * size;

    for (int i = 0; i < size; ++i)
    {
        if (ext_val >= max)
            _putch(full);
        else if (ext_val * 2 >= max)
            _putch(half);
        else
            _putch(empty);

        ext_val -= max;
    }
}
