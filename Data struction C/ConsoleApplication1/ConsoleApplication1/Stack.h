#pragma once
#include "ElemType.h"
//typedef int SElemType;
# include <stdio.h>
# include <stdlib.h>
# include"visit.h"
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0

# define STACK_INIT_SIZE 100//顺序表初始内存分配量
# define STACKINCREMENT 10//顺序表额外内存分配量

typedef int Status;

typedef struct {//顺序栈
	SElemType* base, * top;//栈底，栈顶指针(栈底指向第一个元素，栈顶指向最后一个元素的下一个位置)
	int stacksize;//所占内存大小
}SqStack;

typedef struct SNode {//单链栈的结点
	SElemType data;
	SNode* next;
}SNode, * SLink;
typedef struct {//单链栈
	SLink top, base;//栈顶栈底指针(栈顶即头结点，栈底即尾结点)
	int len;//长度
}LinkStack;

Status InitStackSq(SqStack& S);
Status InitStack(LinkStack& S);
Status DestroyStackSq(SqStack& S);
Status DestroyStack(LinkStack& S);
Status ClearStackSq(SqStack& S);
Status ClearStack(LinkStack& S);
Status StackEmptySq(SqStack S);
Status StackEmpty(LinkStack S);
int StackLengthSq(SqStack S);
int StackLength(LinkStack S);
Status GetTopSq(SqStack S, SElemType& e);
Status GetTop(LinkStack S, SElemType& e);
Status PushSq(SqStack& S, SElemType e);
Status Push(LinkStack& S, SElemType e);
Status PopSq(SqStack& S, SElemType& e);
Status Pop(LinkStack& s, SElemType& e);
Status StackTraverseSq(SqStack S, Status(*visit)(SElemType));
Status StackTraverse(LinkStack S, Status(*visit)(SElemType));