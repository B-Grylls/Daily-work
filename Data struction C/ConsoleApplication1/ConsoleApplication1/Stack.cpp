# include "Stack.h"


Status InitStackSq(SqStack& S) {
	//初始化一个顺序栈为空栈
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}//InitStackSq

Status InitStack(LinkStack& S) {
	//初始化一个链栈为空栈
	S.base = (SLink)malloc(sizeof(SNode));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.base->next = NULL;
	S.len = 0;
	return OK;
}//InitStack

Status DestroyStackSq(SqStack& S) {
	//销毁顺序栈
	free(S.base);
	S.base = NULL;
	S.top = NULL;
	S.stacksize = 0;
	return OK;
}//DestroyStackSq

Status DestroyStack(LinkStack& S) {
	//销毁链栈
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
	//清空顺序栈
	S.top = S.base;
	return OK;
}//ClearStackSq

Status ClearStack(LinkStack& S) {
	//清空链栈
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
	//顺序栈是否为空
	if (S.top == S.base) return TRUE;
	else return FALSE;
}//StackEmptySq

Status StackEmpty(LinkStack S) {
	//链栈是否为空
	if (S.top == S.base) return TRUE;
	else return FALSE;
}//StackEmpty

int StackLengthSq(SqStack S) {
	//返回顺序表的元素个数
	return S.top - S.base;
}//StackLengthSq

int StackLength(LinkStack S) {
	//返回链栈的元素个数
	return S.len;
}//StackLength

Status GetTopSq(SqStack S, SElemType& e) {
	//用e返回S的栈顶元素
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}//GetTopSq

Status GetTop(LinkStack S, SElemType& e) {
	//用e返回S的栈顶元素
	if (S.top == S.base) return ERROR;
	e = S.top->next->data;
	return OK;
}//GetTop

Status PushSq(SqStack& S, SElemType e) {
	//元素e入栈
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
	//元素e入栈
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
	//顺序栈S非空时取出栈顶元素给e，S为空时返回ERROR
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
}//PopSq

Status Pop(LinkStack& S, SElemType& e) {
	//链栈S非空时取出栈顶元素给e，S为空时返回ERROR
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
	//遍历顺序栈，从栈底到栈顶
	SElemType* p = S.base;
	for (; p != S.top; p++)
		if (!(*visit)(*p)) return ERROR;
	return OK;
}//StackTraverseSq

Status StackTraverse(LinkStack S, Status(*visit)(SElemType)) {
	//遍历链栈，从栈顶到栈底
	SLink p = S.top->next;
	while (p) {
		if (!(*visit)(p->data)) return ERROR;
		p = p->next;
	}
	return OK;
}//StackTraverse