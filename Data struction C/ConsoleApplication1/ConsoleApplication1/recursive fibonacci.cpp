#include <stdio.h>
int count;
long Fib(unsigned n);
int main() {
	unsigned n;
	long result;
	count = 0;
	printf("Input the order number of fibonacci sequence: ");
	scanf_s("%u", &n);
	result = Fib(n);
	printf("The %d-th fibonacci number is: %ld\n The frequency of using function Fib is: %d",n, result, count);
	return 0;
}

long Fib(unsigned n) {
	count++;
	if (n == 0) return 0;
	else if (n <= 2) return 1;
	else return Fib(n - 1) + Fib(n - 2);
}