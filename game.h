// 扫雷.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include<stdio.h>
#include<stdlib.h>
#include <setjmp.h>
#include<time.h>

#define ROW 9
#define COL 9
#define ROWS ROW + 2
#define COLS COL + 2
#define EASY_COUNT 10

void game();
void initBoard(char board[][COLS], int row, int col, char ch);
void setBoom(char mine[][COLS], int row, int col);
int wakeOutBoom(char mine[][COLS], int x, int y);
void gameCore(char mine[][COLS], char show[][COLS], int row, int col);
void unfold(char mine[][COLS], char show[][COLS], int x, int y);
void display(char board[][COLS], int row, int col);

// TODO: 在此处引用程序需要的其他标头。
