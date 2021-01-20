#include <stdio.h>
const static int MAX = 100;

int LinearSearch(int[], int, int);//顺序查找(可输入无序数列)
int BinarySearch(int[], int, int);//对分查找
/*总共七大查找算法，待更新*/
int main() {
	int score[MAX];
	int i = -1, n, choice, key, pos = -1;
	do {
		i++;
		printf("input score of student:");
		scanf_s("%d", &score[i]);
	} while (score[i] > 0 && i < MAX);
	n = i;
	do {
		printf("\nwhich element to search:");
		scanf_s("%d", &key);
	} while (key < 0);
	do {
		printf("\nlinear search:1\nbinary search:2\nwhich type of search:\n");
		scanf_s("%d", &choice);
	} while (choice < 1 || choice>2);
	switch (choice) {
	case 1:pos = LinearSearch(score, key, n);
		break;
	case 2:pos = BinarySearch(score, key, n);
		break;
	default:printf("without search!\n");
	}
	if (pos != -1)
		printf("\nthe position of the element is:%d\n", pos + 1);
	else printf("NOT FOUND!\n");
}

int LinearSearch(int set[], int key, int n) {//从头到尾找第一个遇到的相同元素的位置，i表示第i+1个数
	int i;
	for (i = 0; i < n; i++) {
		if (set[i] == key)
			return i;
	}
	return -1;
}

int BinarySearch(int set[], int key, int n) {//输入升序序列，二分法查找位置
	int low = 0, high = n - 1, mid;
	while (high >= low) {
		//mid = (low + high) / 2;  这种low+high有可能数据溢出，修改为下
		mid = low + (high - low) / 2;
		if (set[mid] < key)
			low = mid + 1;
		else if (set[mid] > key)
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

