#pragma once
#include<windows.h>
#include<iostream>
using namespace std;
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 1286
void gotoRowCol(int rpos, int cpos);
void SetClr(int clr);
void getRowColbyLeftClick(int& rpos, int& cpos);
void MygetRowColbyLeftClick2(int& rpos, int& cpos, bool& clicked);



