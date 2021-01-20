# include"Queue.h"


Status InitQueue(LinkQueue& Q) {
	//��ʼ������Ϊ��
	Q.front = (QLink)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	Q.rear = Q.front;
	Q.len = 0;
	return OK;
}//InitQueue

Status InitQueueSq(SqQueue& Q) {
	Q.base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;
	return OK;
}//InitQueueSq

Status DestroyQueue(LinkQueue& Q) {
	//���ٶ���
	while (Q.front) {
		QLink p = Q.front;
		Q.front = Q.front->next;
		free(p);
	}
	Q.len = 0;
	Q.rear = NULL;
	return OK;
}//DestroyQueue

Status DestroyQueueSq(SqQueue& Q) {
	//����ѭ������
	free(Q.base);
	Q.front = Q.rear = 0;
	return OK;
}//DestroyQueueSq

Status ClearQueue(LinkQueue& Q) {
	//��ն���
	//QLink p���������ﶨ��Ͳ�warning
	while (Q.front != Q.rear) {
		QLink p = Q.front;
		Q.front = Q.front->next;
		free(p);
	}
	Q.len = 0;
	return OK;
}//ClearQueue

Status ClearQueueSq(SqQueue& Q) {
	//���ѭ������
	Q.front = Q.rear = 0;
	return OK;
}//ClearQueueSq

Status QueueEmpty(LinkQueue Q) {
	//�����Ƿ�Ϊ��
	if (Q.front == Q.rear) return TRUE;
	else return FALSE;
}//QueueEmpty

Status QueueEmptySq(SqQueue Q) {
	//ѭ�������Ƿ�Ϊ��
	if (Q.front == Q.rear) return TRUE;
	else return FALSE;
}//QueueEmptySq

int QueueLength(LinkQueue Q) {
	//���ض����е�Ԫ����
	return Q.len;
}//QueueLength

int QueueLengthSq(SqQueue Q) {
	//����ѭ�������е�Ԫ����
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}//QueueLengthSq

Status GetHead(LinkQueue Q, QElemType& e) {
	//�����в��գ�����e���ض�ͷԪ�أ����򷵻�ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.front->next->data;
	return OK;
}//GetHead

Status GetHeadSq(SqQueue Q, QElemType& e) {
	//��e����ѭ�����еĶ�ͷԪ�أ�������Ϊ�գ���������ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	return OK;
}//GetHeadSq

Status EnQueue(LinkQueue& Q, QElemType e) {
	//�ڶ��еĶ�β����ֵΪe������Ԫ��
	QLink p = (QLink)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	Q.len++;
	return OK;
}//EnQueue

Status EnQueueSq(SqQueue& Q, QElemType e) {
	//��ѭ�����ж�β����ֵΪe������Ԫ�أ�����������ERROR
	if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}//EnQueueSq

Status DeQueue(LinkQueue& Q, QElemType& e) {
	//�����в�����ɾ����ͷԪ�ز���e���أ�����������ERROR
	if (Q.front == Q.rear) return ERROR;
	QLink p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (p == Q.rear) Q.rear = Q.front;
	free(p);
	Q.len--;
	return OK;
}//DeQueue

Status DeQueueSq(SqQueue& Q, QElemType& e) {
	//�����в�����ɾ����ͷԪ�ز���e���أ�����������ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}//DeQueueSq

Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType)) {
	//�������У��ӱ�ͷ����β
	QLink p = Q.front->next;
	while (p) {
		if (!(*visit)(p->data)) return ERROR;
		p = p->next;
	}
	return OK;
}//QueueTraverse

Status QueueTraverseSq(SqQueue Q, Status(*visit)(QElemType)) {
	//����ѭ�����У���front��rear��ǰһλ��
	int k = Q.front;
	while (k != Q.rear) {
		if (!(*visit)(Q.base[k])) return ERROR;
		k = (k + 1) % MAXQSIZE;
	}
	return OK;
}//QueueTraverseSq