#include "game.h"

void mnue() {
	printf("###############################################\n");
	printf("################    1.start    ################\n");
	printf("################    0.exit     ################\n");
	printf("###############################################\n");
}

void test() {
	// ��ʼ������
	srand((unsigned int)time(NULL));
	int input = 0;

	do {
		mnue(); // ��ӡ�˵�
		printf("������ѡ�\n");
		scanf_s("%d", &input);

		switch (input) {

			case 1: game(); break;
			case 0: printf("�˳���Ϸ, �ڴ��´�����\n"); break;
			default:printf("ѡ�����, ��������������:\n"); break;

		}

	} while (input);

}

int main() {

	test();
	
	return 0;
}