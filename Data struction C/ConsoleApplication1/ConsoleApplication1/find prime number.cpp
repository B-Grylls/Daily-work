#include <stdio.h>
#include<math.h>
const static int N = 1000;

int main() {//ɸ��ɸ��n�������еĺ�����õ�������������������
	int number[N] = {0};
	int n,i,j;
	printf("find all prime number within [1,n],n<=%d, n=", N - 1);
	do {
		scanf_s("%d", &n);
	} while (n<0 || n>N - 1);
	for (i = 2; i <= n; i++)
		number[i] = i;
	for (i = 2; i <= sqrt(n); i++)//ȡ2-sart(n)��ѭ��
		for (j = i + 1; j <= n; j++)//���ں���ÿһ�����䱶����������Ϊ0
			if (number[i] != 0 && number[j] != 0 && number[j] % number[i] == 0)
				number[j] = 0;
	for (i = 2; i <= n; i++)
		if (number[i] != 0)
			printf("%d ", number[i]);
}