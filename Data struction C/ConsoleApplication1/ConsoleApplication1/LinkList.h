#pragma once
# include <stdio.h>
# include <stdlib.h>
# include "visit.h"
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0

typedef int LElemType;

typedef int Status;
typedef struct LNode {//结点
	LElemType data;
	LNode* next;
}*Link, * Position;
typedef struct {//链表
	Link head, tail;//头尾指针
	int len;//链表长度，元素个数，不含头结点
}LinkList;

void FreeNode(Link& p);
Status InitList(LinkList&);
Status DestoryList(LinkList&);
Status ClearList(LinkList& L);
Status InsFirst(Link h, Link s);
Status DelFirst(Link h, Link& q);
Status Append(LinkList& L, Link s);
Status Remove(LinkList& L, Link& q);
Status InsBefore(LinkList& L, Link& p, Link s);
Status InsAfter(LinkList& L, Link& p, Link s);
Status SetCurElem(Link& p, LElemType e);
int GetCurElem(Link p);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
Position GetHead(LinkList L);
Position GetLast(LinkList L);
Position PriorPos(LinkList L, Link p);
Position NextPos(LinkList L, Link p);
Status LocatePos(LinkList L, int i, Link& p);
Position LocateElem(LinkList L, LElemType e, Status(*compare)(LElemType, LElemType));
Status Compare(LElemType a, LElemType b);
Status ListTraverse(LinkList L, Status(*visit)(LElemType));

