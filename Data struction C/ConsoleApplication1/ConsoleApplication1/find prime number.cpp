#include <stdio.h>
#include<math.h>
const static int N = 1000;

int main() {//筛法筛掉n以内所有的合数便得到所有素数，需用数组
	int number[N] = {0};
	int n,i,j;
	printf("find all prime number within [1,n],n<=%d, n=", N - 1);
	do {
		scanf_s("%d", &n);
	} while (n<0 || n>N - 1);
	for (i = 2; i <= n; i++)
		number[i] = i;
	for (i = 2; i <= sqrt(n); i++)//取2-sart(n)的循环
		for (j = i + 1; j <= n; j++)//对于后面每一个是其倍数的数都归为0
			if (number[i] != 0 && number[j] != 0 && number[j] % number[i] == 0)
				number[j] = 0;
	for (i = 2; i <= n; i++)
		if (number[i] != 0)
			printf("%d ", number[i]);
}