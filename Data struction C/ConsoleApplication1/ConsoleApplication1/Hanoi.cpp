#include <stdio.h>

void Hanoi(int n, char a, char b, char c);//move top n disks from a to b by means of c 
void Move(int n, char a, char b);//move n-th disk from a to b
int main() {
	int n;
	printf("Input the number of the disks: ");
	scanf_s("%d", &n);
	printf("Steps of moving %d disks from A to B by means of C\n", n);
	Hanoi(n, 'A', 'B', 'C');
	return 0;
}

void Hanoi(int n, char a, char b, char c) {
	if (1 == n) {
		Move(1, a, b);
	}
	else{
		Hanoi(n - 1, a, c, b);
		Move(n, a, b);
		Hanoi(n - 1, c, b, a);
	}
}

void Move(int n, char a, char b) {
	printf("move %d: from %c to %c \n", n, a, b);
}