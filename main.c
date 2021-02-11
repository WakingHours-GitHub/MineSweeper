#include "game.h"

void mnue() {
	printf("###############################################\n");
	printf("################    1.start    ################\n");
	printf("################    0.exit     ################\n");
	printf("###############################################\n");
}

void test() {
	// 初始化种子
	srand((unsigned int)time(NULL));
	int input = 0;

	do {
		mnue(); // 打印菜单
		printf("请输入选项：\n");
		scanf_s("%d", &input);

		switch (input) {

			case 1: game(); break;
			case 0: printf("退出游戏, 期待下次游玩\n"); break;
			default:printf("选项错误, 请重新输入数字:\n"); break;

		}

	} while (input);

}

int main() {

	test();
	
	return 0;
}