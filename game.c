// game.c: 定义应用程序的入口点。
//

#include "game.h"

int isWin = 0; // 声明全局变量(用于判断赢)

void game() {
	// 两个棋盘，一个是雷盘,一个是展示盘
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };

	// 棋盘分别初始化
	initBoard(mine, ROWS, COLS, 'O');
	initBoard(show, ROWS, COLS, '#');

	// 设置雷
	setBoom(mine, ROW, COL);

	// 游戏的核心部分
	gameCore(mine, show, ROW, COL);
}


// 初始化棋盘, 
void initBoard(char board[][COLS], int rows, int cols, char ch) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = ch;
		}
	}
}

// 根据EASY_COUNT设置雷的个数
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

// 计算x,y周围雷的个数
int wakeOutBoom(char mine[][COLS], int x, int y) {
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (mine[i][j] == '*')  count++;
		}
	}
	return count++;
}

// 游戏的核心部分
void gameCore(char mine[][COLS], char show[][COLS], int row, int col) {
	int x = 0, y = 0;
	while (isWin < ROW * COL - EASY_COUNT) {

		// 作弊（显示当前的雷盘）（测试用）
		//display(mine, ROW, COL);
		//printf("\n\n\n"); // 用于分割

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
				break; // 退出游戏
				
				
			}
			else if (show[x][y] == '#') {
				// 本次坐标不是雷，并且没有被排过雷
				system("cls");
				// 空白展开算法，用于处理点开后的算法
				unfold(mine, show, x, y);

			}
			else {
				printf("当前输入的坐标已经排过雷了，请重新输入\n");
			}
		}
		else {
			printf("当前输入的坐标不合法，请您重新输入\n");
		}
	}
	if (isWin == ROW * COL - EASY_COUNT) {
		// 赢了
		printf("恭喜您！！!成功排除所有雷\n");
		display(mine, ROW, COL);
	}
}

// 空白展开算法
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

// 打印棋盘
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