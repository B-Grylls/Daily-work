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

# define STACK_INIT_SIZE 100//˳����ʼ�ڴ������
# define STACKINCREMENT 10//˳�������ڴ������

typedef int Status;

typedef struct {//˳��ջ
	SElemType* base, * top;//ջ�ף�ջ��ָ��(ջ��ָ���һ��Ԫ�أ�ջ��ָ�����һ��Ԫ�ص���һ��λ��)
	int stacksize;//��ռ�ڴ��С
}SqStack;

typedef struct SNode {//����ջ�Ľ��
	SElemType data;
	SNode* next;
}SNode, * SLink;
typedef struct {//����ջ
	SLink top, base;//ջ��ջ��ָ��(ջ����ͷ��㣬ջ�׼�β���)
	int len;//����
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