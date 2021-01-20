# include <stdio.h>
# include <stdlib.h>

# define LIST_INIT_SIZE 100//顺序表初始内存分配量
# define LISTINCREMENT 10//顺序表额外内存分配量
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0

typedef int Status;
typedef struct {//顺序表
	int* elem;//基址
	int length;//长度
	int listsize;//内存大小（sizeof int）
}SqList;


Status InitList_Sq(SqList& L) {
	//构建一个空的顺序表
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) exit(OVERFLOW);
	L.listsize = LIST_INIT_SIZE;
	L.length = 0;
	return OK;
}//InitList_Sq

Status DestroyList_Sq(SqList& L) {
	//销毁顺序表
	free(L.elem);
	return OK;
}//DestroyList_Sq

Status ClearList_Sq(SqList& L) {
	//清空顺序表，不需要全部赋值为0
	L.length = 0;
	return OK;
}//ClearList_Sq

Status ListEmpty_Sq(SqList L) {
	//是否为空表，返回true false
	if (L.length == 0) return TRUE;
	else return FALSE;
}//ListEmpty_Sq

Status ListInsert_Sq(SqList& L, int i, int e) {
	//将e插入L中的i位置,1<=i<=L.length+1
	if (i<1 || i>L.length + 1) return ERROR;//i不合法
	if (L.length >= L.listsize) {//内存满了
		int* newbase;
		newbase = (int*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(int));
		if (!newbase) exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	int* p = L.elem+i-1;
	int* q = L.elem + L.length - 1;
	for (; p <= q; q--) *(q + 1) = *q;
	*p = e;
	++L.length;
	return OK;
}//ListInsert_Sq

Status ListDelet_Sq(SqList& L, int i, int& e) {
	//删掉L表中第i个元素并传给e，返回函数状态
	int* p = L.elem + i - 1;
	int* q = L.elem + L.length - 1;
	e = *p;
	for (; p < q; p++) *p = *(p + 1);
	--L.length;
	return OK;
}//ListDelete_Sq

int LocateElem_Sq(SqList L, int e, Status(*compare)(int, int)) {
	//表L中从头查找与e满足compare关系的元素，成功返回位置值1到L.length，失败返回0
	int i = 1;
	int* p = L.elem;
	while (i <= L.length && !(*compare)(*p, e)) {
		p++;
		i++;
	}
	if (i > L.length) return 0;
	else return i;
}//LocateElem_Sq

Status Equal(int a, int b) {
	if (a == b) return TRUE;
	else return FALSE;
}
