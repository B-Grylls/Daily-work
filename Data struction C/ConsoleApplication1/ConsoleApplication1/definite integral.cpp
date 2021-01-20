#include <stdio.h>

double integral(double (*f)(float), float, float);
double F1(float);
double F2(float);
int main() {//对于函数积分的上下限输入以及函数选择输入是否合法均未检查
	int index;
	float a, b;
	printf("F1:1+x*x\nF2:x/(1+x*x)\nchoose function to integral(eg:1): ");
	scanf_s("%d", &index);
	printf("integral from a to b, enter a and b:");
	scanf_s("%f %f", &a, &b);
	if (index == 1)
		printf("F1 function integral: %f", integral(F1, a, b));
	else
		printf("F2 function integral: %f", integral(F2, a, b));
	return 0;
}

double integral(double (*f)(float), float a, float b) {//梯形法近似定积分，函数指针指向需要积分的函数，a，b为积分上下界
	double s;
	float h;
	int i, n = 1000;//近似为1000个梯形
	h = (b - a) / n;
	s = ((*f)(a) + (*f)(b)) / 2;
	for (i = 1; i < n; i++)
		s += (*f)(a + i * h);
	return s * h;
}

double F1(float x) {
	return 1 + (double)x * x;//防止float*float存在数据溢出风险
}

double F2(float x) {
	return x / (1 + x * x);
}
