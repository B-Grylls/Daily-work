# include <stdio.h>
# include <stdlib.h>
# define MAXLSIZE 1000
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0

typedef int Status;
typedef struct {//静态链表
	int data;//数据域
	int cur;//指针域
}component, SLinkList[MAXLSIZE];


int LocateElem_SL(SLinkList S, int e) {
	//返回第一个与e相等的元素的下标，若无则返回0
	int i = S[0].cur;//指向第一个节点的指针
	while (i && S[i].data != e)
		i = S[i].cur;
	return i;
}//LocateElem_SL

Status InitList_SL(SLinkList& S) {
	//初始化一个大小为MAXSIZE的静态链表，S[0].cur为头指针
	int i;
	for (i = 0; i < MAXLSIZE - 1; ++i)
		S[i].cur = i + 1;
	S[MAXLSIZE - 1].cur = 0;
	return OK;
}//InitList_SL

int Malloc_SL(SLinkList& Space) {
	//从S中取出第一个节点（S[0].cur指向的）并返回位置值i,i=0表示为空表无法取出，S通常为备用链表
	int i = Space[0].cur;
	if (i) Space[0].cur = Space[i].cur;
	return i;
}//Malloc_SL

Status Free_SL(SLinkList& Space, int k) {
	//将下标为k的结点收回备用链表中
	Space[k].cur = Space[0].cur;
	Space[0].cur = k;
	return OK;
}//Free_SL

void difference(SLinkList& S, int& sp) {
	//在一维数组S中创建集合（A-B）∪（B-A）的静态链表，主表头指针为sp，指向头结点，尾指针为r，备用链表头指针为S[0].cur
	InitList_SL(S);
	int m, n;//A B的元素个数
	int i;
	int t;//新提取结点的指针
	sp = Malloc_SL(S);//主表头指针
	int r = sp;//将通过输入A中元素移动成为尾指针
	scanf_s("%d%d", &m, &n);
	for (i = 1; i <= m; ++i) {//建立含A元素的静态链表,数据从下标2开始
		t = Malloc_SL(S);
		scanf_s("%d", &S[t].data);
		S[r].cur = t;
		r = t;//r最终指向最后一个元素成为尾指针
	}
	S[r].cur = 0;//收尾
	for (i = 1; i <= n; ++i) {//依次输入B元素，相同就删除，不同就链接到表尾
		int b;
		scanf_s("%d", &b);
		int p = sp;//指针p，k用于从主表搜索有没有相同元素
		int k = S[p].cur;//指向第一个结点
		while (k && S[k].data != b) {
			p = k;
			k = S[k].cur;
		}
		if (k == 0) {//无相同元素，表尾链接新结点，并移动尾指针
			t = Malloc_SL(S);
			S[t].data = b;
			S[t].cur = S[r].cur;
			S[r].cur = t;
			r = t;
		}
		else {//有相同元素，删除
			S[p].cur = S[k].cur;
			Free_SL(S, k);
			if (r == k) r = p;//若删除了最后一项，需要移动尾指针到前一结点
		}
	}
}//difference