#include <stdio.h>

/*50！数据计算，超过了数据类型的存储限制，利用数组来实现*/
const int MAX = 1000;//阶乘结果最大位数
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
			up = (number[j] * i + up) / 10;//进到下一位的数值
			number[j] = temp;//留在这一位的数值
			j++;
			if (j >= length && up != 0)//如果循环到了长度末但还有进位，就将长度+1
				length++;
		}
	}
	printf("%d! = ", n);
	for (i = 0; i < length; i++)//倒序输出
		printf("%d", number[length - i - 1]);
}