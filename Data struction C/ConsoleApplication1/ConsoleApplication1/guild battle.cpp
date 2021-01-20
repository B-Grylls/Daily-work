#include <stdio.h>
#include <string.h>

const static int MAX = 100;
int weight[MAX], value[MAX];
int n, limit_weight, max_value, max_weight;
int	best_answer[MAX], answer[MAX];
int raw[MAX], prepared[MAX], final_answer[MAX];
int sum=0;
float max_time;

void print();//打印我们需要的战术分配信息
void DFS(int level,int remain_weight,int curvalue);//在n-1个人中挑出m个使得其总伤害最接近boss血量，选取方法存储在best_answer数组中
void init();//初始化需要循环储存信息的变量
int main() {
	int i,k;
	printf("input the number of combatants n and boss max HP:");
	do {
		scanf_s("%d%d", &n, &limit_weight);
	} while (n <= 0 || n > MAX || limit_weight < 0);
	for (i = 1; i <= n; i++) {
		printf("enter damage of %d-th combatant: ", i);
		scanf_s("%d", &raw[i - 1]);
		sum += raw[i - 1];
	}
	if (sum < limit_weight) {//大家的总输出必须要大于boss血量才可以分配战术
		printf("the total damage is not enough to kill the boss!\n");
		return 0;
	}
	else if (sum == limit_weight) {
		printf("the total damage is exactlly equal to the boss MAX HP!");
		return 0;
	}
	for (k = 1; k <= n; k++) {
		int i,j;
		//将raw去掉第k项再按顺序copy给weight,value
		for (i = 1; i < k; i++)
			weight[i - 1] = value[i - 1] = raw[i - 1];
		for (j = k + 1; j <= n; j++)
			weight[j - 2] = value[j - 2] = raw[j - 1];

		init();
		DFS(0, limit_weight, 0);//n-1人选m人选取完成

		if (((max_weight + raw[k-1] - limit_weight) / (float)raw[k-1]) * 90 + 10 > max_time) {//判断这种方法是否比之前的最优更优
			max_time = ((max_weight + raw[k-1] - limit_weight) / (float)raw[k-1]) * 90 + 10;
			int i,j;
			//将这种最优选取方法加上刚刚抽出的单人，按原次序记录到final_answer
			for (i = 1; i <= k-1; i++)
				final_answer[i - 1] = best_answer[i - 1];
			final_answer[k - 1] = 2;
			for (j = k + 1; j <= n; j++)
				final_answer[j - 1] = best_answer[j - 2];
		}
	}
	print();
	return 0;
}

void init() {
	memset(answer, 0, sizeof(answer));
	memset(best_answer, 0, sizeof(best_answer));
	max_value = max_weight = 0;
}

void print() {
	int i;
	printf("\nthe optimal max_time: %f\n\n", max_time);
	for (i = 1; i <= n; i++) {
		printf("index:%2d damage:%8d choice: %d\n", i, raw[i - 1], final_answer[i - 1]);
	}
}

void DFS(int level, int remain_weight, int curvalue) {
	if (level >= n-1) {
		if (curvalue > max_value) {
			int i;
			max_value = curvalue;
			max_weight = limit_weight-remain_weight;
			for (i = 1; i <= n-1; i++)
				best_answer[i - 1] = answer[i - 1];
		}
	}
	else{
		if (remain_weight > weight[level]) {
			remain_weight -= weight[level];
			curvalue += value[level];
			answer[level] = 1;
			DFS(level + 1, remain_weight, curvalue);
			answer[level] = 0;
			remain_weight += weight[level];
			curvalue -= value[level];
		}
		DFS(level + 1, remain_weight, curvalue);
	}
}