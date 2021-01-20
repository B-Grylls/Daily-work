# include <stdio.h>
# include <stdlib.h>

# define LIST_INIT_SIZE 100//˳����ʼ�ڴ������
# define LISTINCREMENT 10//˳�������ڴ������
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0

typedef int Status;
typedef struct {//˳���
	int* elem;//��ַ
	int length;//����
	int listsize;//�ڴ��С��sizeof int��
}SqList;


Status InitList_Sq(SqList& L) {
	//����һ���յ�˳���
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) exit(OVERFLOW);
	L.listsize = LIST_INIT_SIZE;
	L.length = 0;
	return OK;
}//InitList_Sq

Status DestroyList_Sq(SqList& L) {
	//����˳���
	free(L.elem);
	return OK;
}//DestroyList_Sq

Status ClearList_Sq(SqList& L) {
	//���˳�������Ҫȫ����ֵΪ0
	L.length = 0;
	return OK;
}//ClearList_Sq

Status ListEmpty_Sq(SqList L) {
	//�Ƿ�Ϊ�ձ�����true false
	if (L.length == 0) return TRUE;
	else return FALSE;
}//ListEmpty_Sq

Status ListInsert_Sq(SqList& L, int i, int e) {
	//��e����L�е�iλ��,1<=i<=L.length+1
	if (i<1 || i>L.length + 1) return ERROR;//i���Ϸ�
	if (L.length >= L.listsize) {//�ڴ�����
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
	//ɾ��L���е�i��Ԫ�ز�����e�����غ���״̬
	int* p = L.elem + i - 1;
	int* q = L.elem + L.length - 1;
	e = *p;
	for (; p < q; p++) *p = *(p + 1);
	--L.length;
	return OK;
}//ListDelete_Sq

int LocateElem_Sq(SqList L, int e, Status(*compare)(int, int)) {
	//��L�д�ͷ������e����compare��ϵ��Ԫ�أ��ɹ�����λ��ֵ1��L.length��ʧ�ܷ���0
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
