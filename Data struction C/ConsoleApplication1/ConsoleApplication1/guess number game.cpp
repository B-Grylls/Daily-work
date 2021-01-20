#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 10 times to guess the number created by computer randomly

int main() {
	int guess, number, count, ref;
	char c;
	do {
		count = 0;
		srand(time(NULL));
		number = rand() % 100 + 1;

		do {
			printf("please enter a integer, remaining times = %d\n", 10 - count);
			
			// avoid invalid input
			ref = scanf_s("%d", &guess);
			if (ref != 1) {		
				while (getchar() != '\n');
				printf("your input is invalid, plz enter a new number\n");
				continue;
			}
			count++;

			if (guess > number) printf("try smaller\n");
			else if (guess < number) printf("try bigger\n");
			else printf("correct!\n");
		} while (count < 10 && guess != number);
		printf("you wanna try again? enter Y/y for yes and others for no\n");
		scanf_s(" %c", &c);
	} while ('Y' == c || 'y' == c);
}