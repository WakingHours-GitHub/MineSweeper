// 扫雷.cpp: 定义应用程序的入口点。
//

#include "game.h"

int isWin = 0; // 声明全局变量

void game() {
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	initBoard(mine, ROWS, COLS, 'O');
	initBoard(show, ROWS, COLS, '#');

	setBoom(mine, ROW, COL);

	//display(show, ROW, COL); // 显示一下未开始游戏的布局

	display(mine, ROW, COL);

	gameCore(mine, show, ROW, COL);




}



void initBoard(char board[][COLS], int rows, int cols, char ch) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = ch;
		}
	}
}

void setBoom(char mine[][COLS], int row, int col) {
	for (int i = 0; i < EASY_COUNT;) {
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (mine[x][y] != '*') {
			mine[x][y] = '*';
			i++;
		}
	}
	
}
int wakeOutBoom(char mine[][COLS], int x, int y) {
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j < y + 1; j++) {
			if (mine[i][j] == '*')  count++;
		}
	}
	return count++;
}

void gameCore(char mine[][COLS], char show[][COLS], int row, int col) {
	int x = 0, y = 0;
	while (isWin < ROW * COL - EASY_COUNT) {
		display(show, ROW, COL);
		printf("请输入您要排雷的坐标：\n");
		scanf_s("%d %d", &x, &y);

		if (x >= 1 && x <= row && y >= 1 && y <= col) {
			// 坐标合法
			if (mine[x][y] == '*') {
				// 踩雷
				system("cls");
				printf("您输入了坐标：(%d, %d)。\n很遗憾，您踩到了雷，请重新开始\n",x,y);
				display(mine, row, col);
				printf("\n\n\n");
				break;
				
				
			}
			else if (show[x][y] == '#') {
				// 本次坐标不是雷，并且没有被排过雷
				system("cls");
				unfold(mine, show, x, y);

			}
			else {
				printf("当前输入的坐标已经拍过雷了，请重新输入\n");
			}
		}
		else {
			printf("当前输入的坐标不合法，请您重新输入\n");
		}
	}
	if (isWin == ROW * COL - EASY_COUNT) {
		printf("恭喜您！！!成功排除所有雷\n");
	}
}

void unfold(char mine[][COLS], char show[][COLS], int x, int y) {
	int count = 0;
	isWin++;
	if (!(count = wakeOutBoom(mine, x , y ))) {
		show[x][y] = ' ';
		for (int i = x - 1; i <= x + 1; i++) {
			for (int j = y - 1; j <= y + 1; j++) {
				if ((i > 0 && i <= ROW) && (j > 0 && j <= COL) && (mine[i][j] != '*' && show[i][j] == '#') ) {
					unfold(mine, show, i, j);
				}
			}
		}
	}
	else {
		show[x][y] = '0' + count;
	}
}





void display(char board[][COLS], int row, int col) {
	for (int i = 0; i <= col; i++) printf("%d ", i);
	putchar('\n');
	for (int i = 0; i <= row<<1; i++) printf("_");
	putchar('\n');

	for (int i = 1; i <= row; i++) {
		printf("%d|", i);
		for (int j = 1; j <= col; j++) {
			printf("%c ", board[i][j]);
		}
		putchar('\n');
	}
}