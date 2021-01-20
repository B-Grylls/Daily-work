#pragma once
# include "ElemType.h"
//typedef int QElemType;
# include <stdio.h>
# include <stdlib.h>
# include "visit.h"
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0
# define MAXQSIZE 100


typedef int Status;
typedef struct QNode{//结点
	QElemType data;
	QNode* next;
}QNode, * QLink;
typedef struct {//链队列
	QLink front, rear;//队头指针，队尾指针（相当于链表的头尾指针，尾进头出）
	int len;//队列所含元素数
}LinkQueue;

typedef struct {//循环队列，物理上不循环，从操作上抽象成循环
	QElemType* base;//初始化的存储空间基址
	int front;//头指针，指向头元素
	int rear;//尾指针，指向尾元素的下一个位置
}SqQueue;

Status InitQueue(LinkQueue& Q);
Status InitQueueSq(SqQueue& Q);
Status DestroyQueue(LinkQueue& Q);
Status DestroyQueueSq(SqQueue& Q);
Status ClearQueue(LinkQueue& Q);
Status ClearQueueSq(SqQueue& Q);
Status QueueEmpty(LinkQueue Q);
Status QueueEmptySq(SqQueue Q);
int QueueLength(LinkQueue Q);
int QueueLengthSq(SqQueue Q);
Status GetHead(LinkQueue Q, QElemType& e);
Status GetHeadSq(SqQueue Q, QElemType& e);
Status EnQueue(LinkQueue& Q, QElemType e);
Status EnQueueSq(SqQueue& Q, QElemType e);
Status DeQueue(LinkQueue& Q, QElemType& e);
Status DeQueueSq(SqQueue& Q, QElemType& e);
Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType));
Status QueueTraverseSq(SqQueue Q, Status(*visit)(QElemType));
