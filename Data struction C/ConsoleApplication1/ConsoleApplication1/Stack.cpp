# include "Stack.h"


Status InitStackSq(SqStack& S) {
	//��ʼ��һ��˳��ջΪ��ջ
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}//InitStackSq

Status InitStack(LinkStack& S) {
	//��ʼ��һ����ջΪ��ջ
	S.base = (SLink)malloc(sizeof(SNode));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.base->next = NULL;
	S.len = 0;
	return OK;
}//InitStack

Status DestroyStackSq(SqStack& S) {
	//����˳��ջ
	free(S.base);
	S.base = NULL;
	S.top = NULL;
	S.stacksize = 0;
	return OK;
}//DestroyStackSq

Status DestroyStack(LinkStack& S) {
	//������ջ
	while (S.top) {
		SLink p = S.top->next;
		free(S.top);
		S.top = p;
	}
	S.base = NULL;
	S.len = 0;
	return OK;
}//DestroyStack

Status ClearStackSq(SqStack& S) {
	//���˳��ջ
	S.top = S.base;
	return OK;
}//ClearStackSq

Status ClearStack(LinkStack& S) {
	//�����ջ
	SLink p = NULL;
	while (S.top != S.base) {
		p = S.top;
		S.top = S.top->next;
		free(p);
	}
	S.len = 0;
	return OK;
}//ClearStack

Status StackEmptySq(SqStack S) {
	//˳��ջ�Ƿ�Ϊ��
	if (S.top == S.base) return TRUE;
	else return FALSE;
}//StackEmptySq

Status StackEmpty(LinkStack S) {
	//��ջ�Ƿ�Ϊ��
	if (S.top == S.base) return TRUE;
	else return FALSE;
}//StackEmpty

int StackLengthSq(SqStack S) {
	//����˳����Ԫ�ظ���
	return S.top - S.base;
}//StackLengthSq

int StackLength(LinkStack S) {
	//������ջ��Ԫ�ظ���
	return S.len;
}//StackLength

Status GetTopSq(SqStack S, SElemType& e) {
	//��e����S��ջ��Ԫ��
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}//GetTopSq

Status GetTop(LinkStack S, SElemType& e) {
	//��e����S��ջ��Ԫ��
	if (S.top == S.base) return ERROR;
	e = S.top->next->data;
	return OK;
}//GetTop

Status PushSq(SqStack& S, SElemType e) {
	//Ԫ��e��ջ
	if (S.top - S.base >= S.stacksize) {
		SElemType* newbase = (SElemType*)realloc(S.base, (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(SElemType));
		if (!newbase) exit(OVERFLOW);
		S.base = newbase;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}//PushSq

Status Push(LinkStack& S, SElemType e) {
	//Ԫ��e��ջ
	SLink p = (SLink)malloc(sizeof(SNode));
	if (!p) exit(OVERFLOW);
	p->data = e;
	p->next = S.top->next;
	if (S.base == S.top)
		S.base = p;
	S.top->next = p;
	S.len++;
	return OK;
}//Push

Status PopSq(SqStack& S, SElemType& e) {
	//˳��ջS�ǿ�ʱȡ��ջ��Ԫ�ظ�e��SΪ��ʱ����ERROR
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
}//PopSq

Status Pop(LinkStack& S, SElemType& e) {
	//��ջS�ǿ�ʱȡ��ջ��Ԫ�ظ�e��SΪ��ʱ����ERROR
	if (S.top == S.base) return ERROR;
	SLink p = S.top->next;
	e = p->data;
	S.top->next = p->next;
	if (p == S.base) S.base = S.top;
	free(p);
	S.len--;
	return OK;
}//Pop

Status StackTraverseSq(SqStack S, Status(*visit)(SElemType)) {
	//����˳��ջ����ջ�׵�ջ��
	SElemType* p = S.base;
	for (; p != S.top; p++)
		if (!(*visit)(*p)) return ERROR;
	return OK;
}//StackTraverseSq

Status StackTraverse(LinkStack S, Status(*visit)(SElemType)) {
	//������ջ����ջ����ջ��
	SLink p = S.top->next;
	while (p) {
		if (!(*visit)(p->data)) return ERROR;
		p = p->next;
	}
	return OK;
}//StackTraverse