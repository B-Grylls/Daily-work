# include "LinkList.h"



Status MakeNode(Link& p, int e) {
	//������pָ��ֵΪe�Ľ�㣬�ɹ�����OK��ʧ�ܷ���ERROR
	p = (Link)malloc(sizeof(LNode));
	if (!p) return ERROR;
	p->data = e;
	p->next = NULL;
	return OK;
}//MakeNode 

void FreeNode(Link& p) {
	//�ͷ�pָ��Ľ��
	free(p);
}//FreeNode

Status InitList(LinkList& L) {
	//��������Ա�L
	L.head = (Link)malloc(sizeof(LNode));
	if (!L.head) return ERROR;
	L.head->next = NULL;
	L.tail = L.head;
	L.len = 0;
	//printf("OK\n");
	return OK;
}//InitList

Status DestoryList(LinkList& L) {
	//�������Ա�L
	Link p;
	while (L.head) {//��ͷ��㿪ʼ���ٵ����
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
	//������Ա�ֻʣͷ���
	//���ڴ������Ա��ڲ���Ĭ��L���ڣ���������ͬ
	if (!L.head) return ERROR;//������
	Link q = L.head->next;
	Link p = q;
	while (p && q) {//�ӵ�һ������ͷŵ����һ�����
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
	//hָ��ͷ��㣬��sָ��Ľ������һ�����֮ǰ,Ĭ��*s���ڸ�������
	s->next = h->next;
	h->next = s;
	return OK;
}//InsFirst

Status DelFirst(Link h, Link& q) {
	//hָ��ͷ��㣬ɾ�������еĵ�һ����㣬����q����
	if (!h->next) return ERROR;//�ձ�
	q = h->next;
	h->next = h->next->next;
	q->next = NULL;
	return OK;
}//DelFirst

Status Append(LinkList& L, Link s) {
	//��s��ָ��һ���������������L�����һ����㣬�ƶ�βָ�뵽��󣬸ı�L���ȼ���
	if (!L.head) return ERROR;//������
	L.tail->next = s;
	L.len++;
	while (s->next) {//s�ƶ���β
		s = s->next;
		L.len++;
	}
	L.tail = s;
	return OK;
}//Append

Status Remove(LinkList& L, Link& q) {
	//ɾ��L�е�β��㲢��q���أ��ƶ�βָ�뵽�µ�β���
	if (!L.head) return ERROR;//������
	if (!L.head->next) return ERROR;//�ձ�
	Link p = L.head->next;
	while (p->next != L.tail)//p�ƶ���tailǰһ��
		p = p->next;
	q = L.tail;
	p->next = L.tail->next;
	L.tail = p;
	L.len--;
	return OK;
}//Remove

Status InsBefore(LinkList& L, Link& p, Link s) {
	//pָ��L�е�һ�����(��ͷ���)����sָ��Ľ�����p���֮ǰ�����޸�pָ���½��
	if (p == L.head) return ERROR;//p��ͷ��㣬������ͷ���ǰ������
	Link q = L.head;//qָ��ͷ���
	while (q->next != p)//�ƶ�q��pǰһ�����
		q = q->next;
	s->next = p;
	q->next = s;
	p = s;
	L.len++;
	return OK;
}//InsBefore

Status InsAfter(LinkList& L, Link& p, Link s) {
	//pָ��L�е�һ����㣬��sָ��Ľ�����p���֮�󣬲��޸�pָ���½��
	//��ΪҪ�޸�p��ָ��p��������ͷ���
	if (p == L.head) return ERROR;//pΪͷ���
	s->next = p->next;
	p->next = s;
	if (L.tail == p)//���p��β��㣬��Ҫ�ƶ�βָ��
		L.tail = s;
	p = s;
	L.len++;
	return OK;
}//InsAfter

Status SetCurElem(Link& p, LElemType e) {
	//pָ�������е�һ����㣬��value e���¸ý���е�����
	//ע���Ƿ�Ķ�����ͷ�������
	p->data = e;
	return OK;
}//SetCurElem

int GetCurElem(Link p) {
	//���ص�ǰ������ݣ�ע���Ƿ���ͷ���
	return p->data;
}//GetCurElem

Status ListEmpty(LinkList L) {
	//�ж��Ƿ�Ϊ����������TRUE��FALSE
	//����L.len�жϣ�L.len=0�����ǿձ�Ҳ���ܲ�����
	if (!L.head) return ERROR;//�����ڣ���ʱ�޷�����L.head->next����
	if (L.head == L.tail && !L.head->next)//�ڶ����߼��жϷ�ֹ��ǿյ�βָ������ָ����ͷ���
		return TRUE;
	else return FALSE;
}//ListEmpty

int ListLength(LinkList L) {
	//����L��Ԫ�ظ���
	//�ú�����������ȷ��L.len��ֵ�����Բ���L.len������ֵ,����ͨ���ṹ�ϵı���������
	if (!L.head) return ERROR;//������
	int length = 0;
	Link p = L.head;
	while (p->next) {//��ͷ����ƶ���β���
		p = p->next;
		length++;
	}
	return length;
}//ListLength

Position GetHead(LinkList L) {
	//����L����ͷ����λ��
	if (!L.head) return NULL;//��Ϊ�գ����ؿ�ָ��
	return L.head;
}//GetHead

Position GetLast(LinkList L) {
	//����L����β����λ��
	if (!L.head) return NULL;//��Ϊ�գ����ؿ�ָ��
	return L.tail;//����Ϊ��ʱ�����ص���ͷ���
}//GetLast

Position PriorPos(LinkList L, Link p) {
	//pָ��L�е�һ����㣬���ظý��ֱ��ǰ����λ�ã������򷵻�NULL
	if (p == L.head) return NULL;//ͷ�����ֱ��ǰ��
	Link q = L.head;
	while (q->next != p)//q�ƶ���p��ǰһ�����
		q = q->next;
	return q;
}//PriorPos

Position NextPos(LinkList L, Link p) {
	//pָ��L�е�һ����㣬���ظý��ֱ�Ӻ�̵�λ�ã������򷵻�NULL
	if (p == L.tail) return NULL;//β�����ֱ�Ӻ��
	return p->next;
}//NextPos

Status LocatePos(LinkList L, int i, Link& p) {
	//��pָ��L�е�i����㲢����OK��iֵ���Ϸ�����ERROR
	//0<=i<=L.len����i=0ʱָ��ͷ���
	if (i<0 || i>L.len) return ERROR;
	p = L.head;
	int k;
	for (k = 0; k < i; ++k)
		p = p->next;
	return OK;
}//LocatePos

Position LocateElem(LinkList L, LElemType e, Status(*compare)(LElemType, LElemType)) {
	//����L�е�һ�����㺯��compare()�ж���ϵ��Ԫ�ص�λ�ã������򷵻�NULL
	if (!L.head ||!L.head->next) return NULL;//�����ڻ��գ�����NULL
	Link p = L.head->next;//pָ��ǰ���
	while (p && !(*compare)(p->data, e))
		p=p->next;
	return p;
}//LocateElem

Status Compare(LElemType a, LElemType b) {
	//����ֵΪa-b
	return a - b;
}//Compare

Status ListTraverse(LinkList L, Status(*visit)(LElemType)) {
	//���ζ�L��ÿ��Ԫ�ص���visit()��һ��ʧ�������ʧ��
	if (!L.head || !L.head->next) return ERROR;//�����ڻ���
	Link p = L.head->next;
	while (p) {
		if (!(*visit)(p->data)) return ERROR;//һ��visitʧ�����̷���ERROR
		p = p->next;
	}
	return OK;
}//ListTraverse

