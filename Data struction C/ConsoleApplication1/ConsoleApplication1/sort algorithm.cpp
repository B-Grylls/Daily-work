#include <stdio.h>
const static int MAX = 100;

void ExchangeSort(int[], int);//��������
void SelectionSort(int[], int);//ѡ������(�����Ż�)
void BubbleSort(int[], int);//ð������
void InsertionSort(int[], int);//��������
void QuickSort(int[], int);//��������(ð���Ż�)
/*�����µ�����ϣ�����ѣ��������鲢��Ͱ������
  �ܹ��˴������㷨��������*/
int main() {//�������򷨣�����
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

void ExchangeSort(int set[], int n) {//��һ�������ÿһ��Ƚϣ���С�ڱ㽻��������ѭ��
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
void SelectionSort(int set[], int n) {//�Ż��������򣬽����������һ���
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

void BubbleSort(int set[], int n) {//�������� ��<�� �㽻��
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

void InsertionSort(int set[], int n) {//ǰi�������źã��жϵ�i+1����Ӧ�ò���ǰ����ĸ�λ��
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
	//ѡȡ��һ��ֵΪkeyֵ����¼��j��ĩβ��ǰѰ�ҵ�һ������key����key��λ����¼��i�ٴ�ǰ���Ѱ�ҵ�һ��С��key����key��λ
	//����������¼����������ݾ������������С�Ĺ�ϵ
	//ѭ������ֱ��������¼���ص�i=j��������keyʼ��������һ����¼���λ��
	//����key����i=j��¼�㣬������������ݶ�����key���Ҳ����ݶ�С��key
	//�ٶ����������ֵݹ���������ͳ��˿�������

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