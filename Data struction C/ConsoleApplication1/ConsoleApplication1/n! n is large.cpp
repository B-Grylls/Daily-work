#include <stdio.h>

/*50�����ݼ��㣬�������������͵Ĵ洢���ƣ�����������ʵ��*/
const int MAX = 1000;//�׳˽�����λ��
int main() {
	int number[MAX] = { 0 };
	int n, i, j, up = 0, temp, length = 1;
	number[0] = 1;
	printf("calculate n! n:");
	do {
		scanf_s("%d", &n);
	} while (n <= 0 || n > 100);
	for (i = 1; i <= n; i++) {
		j = 0;
		while (j < length) {
			temp = (number[j] * i + up) % 10;
			up = (number[j] * i + up) / 10;//������һλ����ֵ
			number[j] = temp;//������һλ����ֵ
			j++;
			if (j >= length && up != 0)//���ѭ�����˳���ĩ�����н�λ���ͽ�����+1
				length++;
		}
	}
	printf("%d! = ", n);
	for (i = 0; i < length; i++)//�������
		printf("%d", number[length - i - 1]);
}