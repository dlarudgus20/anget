#pragma once

#include <stdio.h>
#include <conio.h>

enum Keys
{
    Left = 0x104b,
    Right = 0x104d,
    Top = 0x1048,
    Down = 0x1050,
};

enum class CursorType
{
    No, Solid, Normal
};

void gotoxy(int x, int y);
int wherex();
int wherey();
void setCursorType(CursorType c);

void consize(int width, int height);
void clrscr();
void delay(int ms);

int getkey();

unsigned gettick();

void printbar(int value, int max, int size = 40, char full = '%', char half = '*', char empty = '.');

inline void printclr(unsigned length)
{
    for (unsigned i = 0; i < length; ++i)
        putchar(' ');
}

inline int range(int a, int x, int b)
{
    if (a > b)
        return range(b, x, a);

    if (a > x)
        return a;
    else if (b < x)
        return b;
    else
        return x;
}
