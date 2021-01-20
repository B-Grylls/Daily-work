# include "LinkList.h"



Status MakeNode(Link& p, int e) {
	//分配由p指向值为e的结点，成功返回OK，失败返回ERROR
	p = (Link)malloc(sizeof(LNode));
	if (!p) return ERROR;
	p->data = e;
	p->next = NULL;
	return OK;
}//MakeNode 

void FreeNode(Link& p) {
	//释放p指向的结点
	free(p);
}//FreeNode

Status InitList(LinkList& L) {
	//构造空线性表L
	L.head = (Link)malloc(sizeof(LNode));
	if (!L.head) return ERROR;
	L.head->next = NULL;
	L.tail = L.head;
	L.len = 0;
	//printf("OK\n");
	return OK;
}//InitList

Status DestoryList(LinkList& L) {
	//销毁线性表L
	Link p;
	while (L.head) {//从头结点开始销毁到最后
		p = L.head;
		L.head = L.head->next;
		free(p);
	}
	L.tail = NULL;
	L.len = 0;
	//printf("OK\n");
	return OK;
}//DestoryList

Status ClearList(LinkList& L) {
	//清空线性表，只剩头结点
	//对于处理线性表内部的默认L存在，后续函数同
	if (!L.head) return ERROR;//表不存在
	Link q = L.head->next;
	Link p = q;
	while (p && q) {//从第一个结点释放到最后一个结点
		p = p->next;
		free(q);
		q = p;
	}
	L.head->next = NULL;
	L.tail = L.head;
	L.len = 0;
	return OK;
}//ClearList

Status InsFirst(Link h, Link s) {
	//h指向头结点，将s指向的结点插入第一个结点之前,默认*s不在该链表中
	s->next = h->next;
	h->next = s;
	return OK;
}//InsFirst

Status DelFirst(Link h, Link& q) {
	//h指向头结点，删除链表中的第一个结点，并用q返回
	if (!h->next) return ERROR;//空表
	q = h->next;
	h->next = h->next->next;
	q->next = NULL;
	return OK;
}//DelFirst

Status Append(LinkList& L, Link s) {
	//将s所指的一串结点链接在链表L的最后一个结点，移动尾指针到最后，改变L长度计数
	if (!L.head) return ERROR;//表不存在
	L.tail->next = s;
	L.len++;
	while (s->next) {//s移动到尾
		s = s->next;
		L.len++;
	}
	L.tail = s;
	return OK;
}//Append

Status Remove(LinkList& L, Link& q) {
	//删除L中的尾结点并用q返回，移动尾指针到新的尾结点
	if (!L.head) return ERROR;//表不存在
	if (!L.head->next) return ERROR;//空表
	Link p = L.head->next;
	while (p->next != L.tail)//p移动到tail前一个
		p = p->next;
	q = L.tail;
	p->next = L.tail->next;
	L.tail = p;
	L.len--;
	return OK;
}//Remove

Status InsBefore(LinkList& L, Link& p, Link s) {
	//p指向L中的一个结点(非头结点)，将s指向的结点插入p结点之前，并修改p指向新结点
	if (p == L.head) return ERROR;//p是头结点，不能往头结点前插入结点
	Link q = L.head;//q指向头结点
	while (q->next != p)//移动q到p前一个结点
		q = q->next;
	s->next = p;
	q->next = s;
	p = s;
	L.len++;
	return OK;
}//InsBefore

Status InsAfter(LinkList& L, Link& p, Link s) {
	//p指向L中的一个结点，将s指向的结点插入p结点之后，并修改p指向新结点
	//因为要修改p的指向，p不可以是头结点
	if (p == L.head) return ERROR;//p为头结点
	s->next = p->next;
	p->next = s;
	if (L.tail == p)//如果p是尾结点，需要移动尾指针
		L.tail = s;
	p = s;
	L.len++;
	return OK;
}//InsAfter

Status SetCurElem(Link& p, LElemType e) {
	//p指向链表中的一个结点，用value e更新该结点中的数据
	//注意是否改动的是头结点数据
	p->data = e;
	return OK;
}//SetCurElem

int GetCurElem(Link p) {
	//返回当前结点数据，注意是否是头结点
	return p->data;
}//GetCurElem

Status ListEmpty(LinkList L) {
	//判断是否为空链表，返回TRUE，FALSE
	//不用L.len判断，L.len=0可能是空表也可能不存在
	if (!L.head) return ERROR;//表不存在，此时无法进行L.head->next操作
	if (L.head == L.tail && !L.head->next)//第二条逻辑判断防止表非空但尾指针错误的指向了头结点
		return TRUE;
	else return FALSE;
}//ListEmpty

int ListLength(LinkList L) {
	//返回L中元素个数
	//该函数可能用来确定L.len的值，所以不用L.len做返回值,而是通过结构上的遍历来计数
	if (!L.head) return ERROR;//表不存在
	int length = 0;
	Link p = L.head;
	while (p->next) {//从头结点移动到尾结点
		p = p->next;
		length++;
	}
	return length;
}//ListLength

Position GetHead(LinkList L) {
	//返回L表中头结点的位置
	if (!L.head) return NULL;//表为空，返回空指针
	return L.head;
}//GetHead

Position GetLast(LinkList L) {
	//返回L表中尾结点的位置
	if (!L.head) return NULL;//表为空，返回空指针
	return L.tail;//当表为空时，返回的是头结点
}//GetLast

Position PriorPos(LinkList L, Link p) {
	//p指向L中的一个结点，返回该结点直接前驱的位置，若无则返回NULL
	if (p == L.head) return NULL;//头结点无直接前驱
	Link q = L.head;
	while (q->next != p)//q移动到p的前一个结点
		q = q->next;
	return q;
}//PriorPos

Position NextPos(LinkList L, Link p) {
	//p指向L中的一个结点，返回该结点直接后继的位置，若无则返回NULL
	if (p == L.tail) return NULL;//尾结点无直接后继
	return p->next;
}//NextPos

Status LocatePos(LinkList L, int i, Link& p) {
	//将p指向L中第i个结点并返回OK，i值不合法返回ERROR
	//0<=i<=L.len，当i=0时指向头结点
	if (i<0 || i>L.len) return ERROR;
	p = L.head;
	int k;
	for (k = 0; k < i; ++k)
		p = p->next;
	return OK;
}//LocatePos

Position LocateElem(LinkList L, LElemType e, Status(*compare)(LElemType, LElemType)) {
	//返回L中第一个满足函数compare()判定关系的元素的位置，若无则返回NULL
	if (!L.head ||!L.head->next) return NULL;//表不存在或表空，返回NULL
	Link p = L.head->next;//p指向当前结点
	while (p && !(*compare)(p->data, e))
		p=p->next;
	return p;
}//LocateElem

Status Compare(LElemType a, LElemType b) {
	//返回值为a-b
	return a - b;
}//Compare

Status ListTraverse(LinkList L, Status(*visit)(LElemType)) {
	//依次对L中每个元素调用visit()，一旦失败则操作失败
	if (!L.head || !L.head->next) return ERROR;//表不存在或表空
	Link p = L.head->next;
	while (p) {
		if (!(*visit)(p->data)) return ERROR;//一旦visit失败立刻返回ERROR
		p = p->next;
	}
	return OK;
}//ListTraverse

