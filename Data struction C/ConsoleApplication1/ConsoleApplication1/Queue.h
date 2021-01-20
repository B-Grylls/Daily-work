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
typedef struct QNode{//���
	QElemType data;
	QNode* next;
}QNode, * QLink;
typedef struct {//������
	QLink front, rear;//��ͷָ�룬��βָ�루�൱�������ͷβָ�룬β��ͷ����
	int len;//��������Ԫ����
}LinkQueue;

typedef struct {//ѭ�����У������ϲ�ѭ�����Ӳ����ϳ����ѭ��
	QElemType* base;//��ʼ���Ĵ洢�ռ��ַ
	int front;//ͷָ�룬ָ��ͷԪ��
	int rear;//βָ�룬ָ��βԪ�ص���һ��λ��
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
