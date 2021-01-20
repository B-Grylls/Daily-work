#include <stdio.h>
const static int MAX = 100;

void ExchangeSort(int[], int);//交换排序
void SelectionSort(int[], int);//选择排序(交换优化)
void BubbleSort(int[], int);//冒泡排序
void InsertionSort(int[], int);//插入排序
void QuickSort(int[], int);//快速排序(冒泡优化)
/*待更新的排序：希尔，堆，基数，归并，桶，计数
  总共八大排序算法，待更新*/
int main() {//多种排序法，降序
	int score[MAX];
	int i = -1, j, n, choice;
	do {
		i++;
		printf("input score of student:");
		scanf_s("%d", &score[i]);
	} while (score[i] > 0 && i<MAX);
	n = i;
	do {
		printf("exchange sort:1\nselection sort:2\nbubble sort:3\ninsertion sort:4\nquick sort:5\nwhich type of sort:\n");
		scanf_s("%d", &choice);
	} while (choice < 1 || choice>5);
	switch (choice) {
	case 1:ExchangeSort(score, n);
		break;
	case 2:SelectionSort(score, n);
		break;
	case 3:BubbleSort(score, n);
		break;
	case 4:InsertionSort(score, n);
		break;
	case 5:QuickSort(score, n);
		break;
	default:printf("without sort!\n");
	}
	printf("Sorted Array: ");
	for (j = 0; j < n; j++)
		printf("%d  ", score[j]);
	return 0;
}

void ExchangeSort(int set[], int n) {//第一项与后面每一项比较，若小于便交换，依次循环
	int i, j, copy;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (set[i] < set[j]) {
				copy = set[i];
				set[i] = set[j];
				set[j] = copy;
			}
		}
	}
}
void SelectionSort(int set[], int n) {//优化交换排序，仅与后面最大的一项交换
	int i, j, max, copy;
	for (i = 0; i < n - 1; i++) {
		max = i;
		for (j = i + 1; j < n; j++) {
			if (set[max] < set[j])
				max = j;
		}
		if (max != i) {
			copy = set[i];
			set[i] = set[max];
			set[max] = copy;
		}
	}
}

void BubbleSort(int set[], int n) {//相邻数若 左<右 便交换
	int i, j, copy;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (set[j] < set[j + 1]) {
				copy = set[j];
				set[j] = set[j + 1];
				set[j + 1] = copy;
			}
		}
	}
}

void InsertionSort(int set[], int n) {//前i个数已排好，判断第i+1个数应该插入前面的哪个位置
	int i, j, k, copy;
	for (i = 1; i < n; i++) {
		k = i - 1;
		copy = set[i];
		while (set[k] < copy && k >= 0) {
			set[k + 1] = set[k];
			k -= 1;
		}
		set[k + 1] = copy;
	}
}


void QuickSort(int set[], int n) {
	//选取第一个值为key值，记录点j从末尾向前寻找第一个大于key的与key换位，记录点i再从前向后寻找第一个小于key的与key换位
	//这样两个记录点两侧的数据就满足了左大右小的关系
	//循环操作直到两个记录点重叠i=j，过程中key始终在其中一个记录点的位置
	//最终key必在i=j记录点，且满足左侧数据都大于key，右侧数据都小于key
	//再对左右两部分递归这种排序就成了快速排序法

	if (n > 1) {
		int i = 0, j = n - 1, key;
		key = set[0];
		while (i != j) {
			while (set[j] <= key && j > i)
				j--;
			set[i] = set[j];
			while (set[i] >= key && j > i)
				i++;
			set[j] = set[i];
		}
		set[i] = key;
		QuickSort(set, i + 1);
		//if (i + 1 <= n - 1)
		QuickSort(&set[i + 1], n - i - 1);
	}
}