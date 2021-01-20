# include"Queue.h"


Status InitQueue(LinkQueue& Q) {
	//初始化队列为空
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
	//销毁队列
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
	//销毁循环队列
	free(Q.base);
	Q.front = Q.rear = 0;
	return OK;
}//DestroyQueueSq

Status ClearQueue(LinkQueue& Q) {
	//清空队列
	//QLink p；放在这里定义就不warning
	while (Q.front != Q.rear) {
		QLink p = Q.front;
		Q.front = Q.front->next;
		free(p);
	}
	Q.len = 0;
	return OK;
}//ClearQueue

Status ClearQueueSq(SqQueue& Q) {
	//清空循环队列
	Q.front = Q.rear = 0;
	return OK;
}//ClearQueueSq

Status QueueEmpty(LinkQueue Q) {
	//队列是否为空
	if (Q.front == Q.rear) return TRUE;
	else return FALSE;
}//QueueEmpty

Status QueueEmptySq(SqQueue Q) {
	//循环队列是否为空
	if (Q.front == Q.rear) return TRUE;
	else return FALSE;
}//QueueEmptySq

int QueueLength(LinkQueue Q) {
	//返回队列中的元素数
	return Q.len;
}//QueueLength

int QueueLengthSq(SqQueue Q) {
	//返回循环队列中的元素数
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}//QueueLengthSq

Status GetHead(LinkQueue Q, QElemType& e) {
	//若队列不空，则用e返回队头元素，否则返回ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.front->next->data;
	return OK;
}//GetHead

Status GetHeadSq(SqQueue Q, QElemType& e) {
	//用e返回循环队列的队头元素，若队列为空，函数返回ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	return OK;
}//GetHeadSq

Status EnQueue(LinkQueue& Q, QElemType e) {
	//在队列的队尾插入值为e的数据元素
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
	//在循环队列队尾插入值为e的数据元素，若已满，则ERROR
	if ((Q.rear + 1) % MAXQSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}//EnQueueSq

Status DeQueue(LinkQueue& Q, QElemType& e) {
	//若队列不空则删除表头元素并用e返回，否则函数返回ERROR
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
	//若队列不空则删除表头元素并用e返回，否则函数返回ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}//DeQueueSq

Status QueueTraverse(LinkQueue Q, Status(*visit)(QElemType)) {
	//遍历队列，从表头到表尾
	QLink p = Q.front->next;
	while (p) {
		if (!(*visit)(p->data)) return ERROR;
		p = p->next;
	}
	return OK;
}//QueueTraverse

Status QueueTraverseSq(SqQueue Q, Status(*visit)(QElemType)) {
	//遍历循环队列，从front到rear的前一位置
	int k = Q.front;
	while (k != Q.rear) {
		if (!(*visit)(Q.base[k])) return ERROR;
		k = (k + 1) % MAXQSIZE;
	}
	return OK;
}//QueueTraverseSq