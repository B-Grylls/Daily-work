# include"BiTree.h"



Status InitBiTree(BiTree& T) {
	//��ʼ��һ���յĶ�����
	T = NULL;
	return OK;
}//InitBiTree

Status CreateBiTree(BiTree& T) {
	//������������㣬�ո��ַ���ʾ����
	//ע���ַ���Ҫһ�������룬����scanf�ͻ��ظ���ȡ�س�
	char ch;
	scanf_s("%c", &ch);
	if (ch == ' ') T = NULL;
	else {
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = ch;
		T->flag = 0;//�����Ϊ�ǵݹ�����������
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}//CreatBiTree

Status DestroyBiTree(BiTree& T) {
	//����һ��������
	if (!T) return OK;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
	T = NULL;
	return OK;
}//DestroyBiTree

Status ClearBiTree(BiTree& T) {
	//��ն�����
	if (!T) return OK;
	ClearBiTree(T->lchild);
	ClearBiTree(T->rchild);
	free(T);
	T = NULL;
	return OK;
}//ClearBiTree

Status BiTreeEmpty(BiTree T) {
	//�б�������Ƿ�Ϊ��
	if (!T) return TRUE;
	else return FALSE;
}//BiTreeEmpty

Status CopyBiTree(BiTree T, BiTree& S) {
	//������T���Ƹ�S���ݹ��㷨
	if (!T) S = NULL;
	else {
		S = (BiTNode*)malloc(sizeof(BiTNode));
		if (!S) return ERROR;
		S->data = T->data;
		BiTree Left, Right;
		CopyBiTree(T->lchild, Left);
		CopyBiTree(T->rchild, Right);
		S->lchild = Left;
		S->rchild = Right;
	}
	return OK;
}//CopyBiTree

Status CopyBiTree_nrc1(BiTree T, BiTree& S) {
	//������T���Ƹ�S���ǵݹ��㷨������ջ
	LinkStack A, B;
	BiTNode* p = T, * q;
	InitStack(A);
	InitStack(B);
	if (!T) S = NULL;
	else {
		S = (BiTNode*)malloc(sizeof(BiTNode));
		if (!S) return ERROR;
		S->data = T->data;
		S->lchild = S->rchild = NULL;
	}
	q = S;
	while (p || !StackEmpty(A)) {
		if (p) {
			Push(A, p);
			Push(B, q);
			if (p->lchild) {
				q->lchild = (BiTNode*)malloc(sizeof(BiTNode));
				if (!q->lchild) return ERROR;
				q->lchild->data = p->lchild->data;
				q->lchild->lchild = q->lchild->rchild = NULL;
			}
			p = p->lchild;
			q = q->lchild;
		}
		else {
			Pop(A, p);
			Pop(B, q);
			if (p->rchild) {
				q->rchild = (BiTNode*)malloc(sizeof(BiTNode));
				if (!q->rchild) return ERROR;
				q->rchild->data = p->rchild->data;
				q->rchild->lchild = q->rchild->rchild = NULL;
			}
			p = p->rchild;
			q = q->rchild;
		}
	}
	return OK;
}

Status CopyBiTree_nrc2(BiTree T, BiTree& S) {
	//������T���Ƹ�S���ǵݹ��㷨������ջ
	LinkStack A, B;
	BiTNode* p, * q;
	InitStack(A);
	InitStack(B);
	if (!T) S = NULL;
	else {
		S = (BiTNode*)malloc(sizeof(BiTNode));
		if (!S) return ERROR;
		S->data = T->data;
		S->lchild = S->rchild = NULL;
	}
	Push(A, T); Push(B, S);
	while (!StackEmpty(A)) {
		while (GetTop(A, p) && p) {
			GetTop(B, q);
			if (p->lchild) {
				q->lchild = (BiTNode*)malloc(sizeof(BiTNode));
				if (!q->lchild) return ERROR;
				q->lchild->data = p->lchild->data;
				q->lchild->lchild = q->lchild->rchild = NULL;
			}
			Push(A, p->lchild);
			Push(B, q->lchild);
		}
		Pop(A, p);
		Pop(B, q);
		if (!StackEmpty(A)) {
			Pop(A, p);
			Pop(B, q);
			if (p->rchild) {
				q->rchild = (BiTNode*)malloc(sizeof(BiTNode));
				if (!q->rchild) return ERROR;
				q->rchild->data = p->rchild->data;
				q->rchild->lchild = q->rchild->rchild = NULL;
			}
			Push(A, p->rchild);
			Push(B, q->rchild);
		}
	}
	return OK;
}

int BiTreeDepth(BiTree T) {
	//�����������
	if (!T) return 0;
	int a = BiTreeDepth(T->lchild);
	int b = BiTreeDepth(T->rchild);
	int max = a > b ? a : b;
	return max + 1;
}//BiTreeDepth

BiTNode* Root(BiTree T) {
	//���ض�����T�ĸ�
	return T;
}//Root

TElemType Value(BiTree T, BiTNode* e) {
	//������T�н��e��ֵ
	return e->data;
}//Value

Status Assign(BiTree& T, BiTNode* e, TElemType value) {
	//��ֵvalue����������T�н��e
	e->data = value;
	return OK;
}//Assign

BiTNode* Parent(BiTree T, BiTNode* e) {
	//���ض�����T�н��e��parent�����޷���NULL
	if (T == e) return NULL;
	if (!T) return NULL;
	if (T->lchild == e || T->rchild == e) return T;
	BiTNode* node;
	if (node = Parent(T->lchild, e))
		return node;
	else return Parent(T->rchild, e);
}//Parent

BiTNode* LeftChild(BiTree T, BiTNode* e) {
	//���ؽ��e����child�����޷���NULL
	return e->lchild;
}//LeftChild

BiTNode* RightChild(BiTree T, BiTNode* e) {
	//���ؽ��e����child�����޷���NULL
	return e->rchild;
}//RightChild

BiTNode* LeftSibling(BiTree T, BiTNode* e) {
	//���ؽ��e����sibling�����޷���NULL
	if (!T) return NULL;
	if (T == e) return NULL;
	if (T->rchild == e) return T->lchild;
	if (T->lchild == e) return NULL;
	BiTNode* node;
	if (node = LeftSibling(T->lchild, e))
		return node;
	else return LeftSibling(T->rchild, e);
}//LeftSibling

BiTNode* RightSibling(BiTree T, BiTNode* e) {
	//���ؽ��e����sibling�����޷���NULL
	if (!T) return NULL;
	if (T == e) return NULL;
	if (T->lchild == e) return T->rchild;
	if (T->rchild == e) return NULL;
	BiTNode* node;
	if (node = RightSibling(T->lchild, e))
		return node;
	else return RightSibling(T->rchild, e);
}//RightSibling

Status InsertChild(BiTree& T, BiTNode* p, int LR, BiTree& C) {
	//pΪ������T��ĳ����㣬CΪ�ǿն���������T���ཻ��������Ϊ��
	//LR=0||1��ʾ��C���뵽p�����������λ�ã��滻�µ���������C��������λ����
	if (!C || C->rchild) return ERROR;
	BiTNode* node;
	if (LR == 0) {//C����p��������λ��
		node = p->lchild;
		p->lchild = C;
	}
	else {//C����p��������λ��
		node = p->rchild;
		p->rchild = C;
	}
	C->rchild = node;
	return OK;
}//InsertChild

Status DeleteChild(BiTree& T, BiTNode* p, int LR) {
	//pΪ������T�еĽ�㣬ɾ��p����LR=0�����ң�LR=1������
	if (LR == 0) DestroyBiTree(p->lchild);
	else DestroyBiTree(p->rchild);
	return OK;
}//DeleteChild

Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType)) {
	//�������
	if (!T) return OK;
	if (!(*visit)(T->data)) return ERROR;
	if (!PreOrderTraverse(T->lchild, (*visit))) return ERROR;
	if (!PreOrderTraverse(T->rchild, (*visit))) return ERROR;
	return OK;
}//PreOrderTraverse

Status InOrderTraverse(BiTree T, Status(*visit)(TElemType)) {
	//�������
	if (!T) return OK;
	if (!InOrderTraverse(T->lchild, (*visit))) return ERROR;
	if (!(*visit)(T->data)) return ERROR;
	if (!InOrderTraverse(T->rchild, (*visit))) return ERROR;
	return OK;
}//InOrderTraverse

Status AntiInOrderPrint(BiTree T, int depth = 1) {
	//��������������Һ����ӡ��������״
	if (!T) return OK;
	if (!AntiInOrderPrint(T->rchild, depth + 1)) return ERROR;
	for (int i = 1; i < depth; ++i)
		printf(" ");
	printf("%c\n", T->data);
	if (!AntiInOrderPrint(T->lchild, depth + 1)) return ERROR;
	return OK;
}//AntiInOrderPrint

Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType)) {
	//�������
	if (!T) return OK;
	if (!PostOrderTraverse(T->lchild, (*visit))) return ERROR;
	if (!PostOrderTraverse(T->rchild, (*visit))) return ERROR;
	if (!(*visit)(T->data)) return ERROR;
	return OK;
}//PostOrderTraverse

Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType)) {
	//����������ǵݹ飬���ö���
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q, T);
	BiTNode* p;
	while (!QueueEmpty(Q)) {
		DeQueue(Q, p);
		if (!(*visit)(p->data)) return ERROR;
		if (p->lchild)
			EnQueue(Q, p->lchild);
		if (p->rchild)
			EnQueue(Q, p->rchild);
	}
	return OK;
}//LevelOrderTraverse

/*3�ֱ�����2�ַǵݹ���ʽ*/
/*2�ַǵݹ��������ڣ����ڵ�ǰ�о���㣬��ֱ����ջȻ��GetTop(S,p)�ٶ�p����ϸ�жϣ�������ָ��pָ������
������ϸ�жϺ��ٿ��Ƿ���ջ�����Ա�־��������NULLʱǰ�߻�push null��ջ����pop�����������߲�����ջ*/
//����ǰ��ͷ�ļ��н�ջ�Ļ���Ԫ����������ΪBiTNode*
Status PreTraverse(BiTree T, Status(*visit)(TElemType)) {
	//��������ǵݹ�
	LinkStack S;
	InitStack(S);
	Push(S, T);
	BiTNode* p;
	while (!StackEmpty(S)) {
		while (GetTop(S, p) && p) {
			if (!(*visit)(p->data)) return ERROR;
			Push(S, p->lchild);
		}
		Pop(S, p);//ȥNULL
		if (!StackEmpty(S)) {
			Pop(S, p);
			Push(S, p->rchild);
		}
	}
	return OK;
}//PreTraverse

Status PreOrder(BiTree T, Status(*visit)(TElemType)) {
	//��������ǵݹ�
	LinkStack S;
	InitStack(S);
	BiTNode* p = T;
	while (p || !StackEmpty(S)) {
		if (p) {
			if (!(*visit)(p->data)) return ERROR;
			Push(S, p);
			p = p->lchild;
		}
		else {
			Pop(S, p);
			p = p->rchild;
		}
	}
	return OK;
}//PreOrder

Status InTraverse(BiTree T, Status(*visit)(TElemType)) {
	//��������ǵݹ�
	LinkStack S;
	InitStack(S);
	Push(S, T);
	BiTNode* p;
	while (!StackEmpty(S)) {
		while (GetTop(S, p) && p)
			Push(S, p->lchild);
		Pop(S, p);//ȥNULL
		if (!StackEmpty(S)) {
			Pop(S, p);
			if (!(*visit)(p->data)) return ERROR;
			Push(S, p->rchild);
		}
	}
	return OK;
}//InTraverse

Status InOrder(BiTree T, Status(*visit)(TElemType)) {
	//��������ǵݹ�
	LinkStack S;
	InitStack(S);
	BiTNode* p = T;
	while (p || !StackEmpty(S)) {
		if (p) {
			Push(S, p);
			p = p->lchild;
		}
		else {
			Pop(S, p);
			if (!(*visit)(p->data)) return ERROR;
			p = p->rchild;
		}
	}
	return OK;
}//InOrder

Status PostTraverse(BiTree T, Status(*visit)(TElemType)) {
	//��������ǵݹ飬��ʱ��Ҫ�õ������е�flag
	LinkStack S;
	InitStack(S);
	Push(S, T);
	BiTNode* p;
	while (!StackEmpty(S)) {
		while (GetTop(S, p) && p)
			if (!p->lchild || p->lchild->flag == 0)
				Push(S, p->lchild);
			else Push(S, NULL);
		Pop(S, p);//ȥNULL
		if (!StackEmpty(S)) {
			GetTop(S, p);
			if (p->flag == 1) {//���ý���Ǵ���rchild����ʱ�����
				Pop(S, p);
				if (!(*visit)(p->data)) return ERROR;
			}
			else {
				p->flag = 1;
				Push(S, p->rchild);//���ý�����lchild����ʱ�ȴ���rchild
			}
		}
	}
	return OK;
}//PostTraverse

Status PostOrder(BiTree T, Status(*visit)(TElemType)) {
	//��������ǵݹ�
	LinkStack S;
	InitStack(S);
	BiTNode* p = T;
	while (p || !StackEmpty(S)) {
		if (p) {
			Push(S, p);
			p = p->lchild;
		}
		else {
			GetTop(S, p);
			if (p->flag == 1) {
				Pop(S, p);
				if (!(*visit)(p->data)) return ERROR;
				p = NULL;
			}
			else {
				p->flag = 1;
				p = p->rchild;
			}
		}
	}
	return OK;
}//PostOrder

/*�����������ı�������*/

Status CreatBiThrTree(BiThrTree& T) {
	//������������㣬�ո��ַ���ʾ����
	//ע���ַ���Ҫһ�������룬����scanf�ͻ��ظ���ȡ�س�
	char ch;
	scanf_s("%c", &ch);
	if (ch == ' ') T = NULL;
	else {
		if (!(T = (BiThrNode*)malloc(sizeof(BiThrNode))))
			exit(OVERFLOW);
		T->data = ch;
		T->parent = NULL;
		T->LTag = T->RTag = PointerTag::Link;
		CreatBiThrTree(T->lchild);
		if (T->lchild) T->lchild->parent = T;
		CreatBiThrTree(T->rchild);
		if (T->rchild) T->rchild->parent = T;
	}
	return OK;
}//CreatBiTree

Status DestroyBiThrTree(BiThrTree& T) {
	//����һ������������
	if (!T) return OK;
	if (T->LTag == PointerTag::Link)
		DestroyBiThrTree(T->lchild);
	if (T->RTag == PointerTag::Link)
		DestroyBiThrTree(T->rchild);
	free(T);
	T = NULL;
	return OK;
}//DestroyBiTree

Status Threading(BiThrTree& Thrt, BiThrTree T, Status(*OrderThreading)(BiThrTree&, BiThrTree)) {
	//Thrtͷ��㣬��(*OrderThreading)��˳��������������T
	Thrt = (BiThrNode*)malloc(sizeof(BiThrNode));
	if (!Thrt) exit(OVERFLOW);
	Thrt->LTag = PointerTag::Link;
	Thrt->RTag = PointerTag::Thread;
	Thrt->rchild = Thrt;//��ָ���ָ
	if (!T) Thrt->lchild = Thrt;//T����ͷ�����ָ���ָ
	else {
		BiThrNode* pre = Thrt;
		Thrt->lchild = T;
		(*OrderThreading)(pre, T);//����/����/���� ��������T
		Thrt->rchild = pre;
		if (!pre->rchild)
			pre->rchild = Thrt;
	}
	return OK;
}//Threading

Status PreThreading(BiThrTree& pre, BiThrTree p) {
	//����������������T��������Threading�ĺ�������
	if (!p) return OK;
	if (!p->lchild) {
		p->LTag = PointerTag::Thread;
		p->lchild = pre;
	}
	if (!pre->rchild) {
		pre->RTag = PointerTag::Thread;
		pre->rchild = p;
	}
	pre = p;
	if (p->LTag == PointerTag::Link)//p->lchild�����ǰ�汻�����ˣ�˵����������Ϊ�գ�ֱ������
		PreThreading(pre, p->lchild);
	if (p->RTag == PointerTag::Link)
		PreThreading(pre, p->rchild);
	return OK;
}//PreThreading

Status InThreading(BiThrTree& pre, BiThrTree p) {
	//����������������T��������Threading�ĺ�������
	if (!p) return OK;
	InThreading(pre, p->lchild);//��������������ͬ��p->lchildһ��δ�����ģ����Բ����б�Tag
	if (!p->lchild) {
		p->LTag = PointerTag::Thread;
		p->lchild = pre;
	}
	if (!pre->rchild) {
		pre->RTag = PointerTag::Thread;
		pre->rchild = p;
	}
	pre = p;
	InThreading(pre, p->rchild);
	return OK;
}//InThreading

Status PostThreading(BiThrTree& pre, BiThrTree p) {
	//����������������T��������Threading�ĺ�������
	if (!p) return OK;
	PostThreading(pre, p->lchild);
	PostThreading(pre, p->rchild);
	if (!p->lchild) {
		p->LTag = PointerTag::Thread;
		p->lchild = pre;
	}
	if (!pre->rchild) {
		pre->RTag = PointerTag::Thread;
		pre->rchild = p;
	}
	pre = p;
	return OK;
}//PostThreading

Status PreTraverse_Thr(BiThrTree T, Status(*visit)(TElemType)) {
	//��������ǵݹ飬T���Ѿ���Threading�������������������
	BiThrNode* p = T->lchild;//��ʼָ����ڵ�
	while (p != T) {
		if (!(*visit)(p->data)) return ERROR;
		while (p->LTag == PointerTag::Link) {
			p = p->lchild;
			if (!(*visit)(p->data)) return ERROR;
		}
		p = p->rchild;//��ʱ����p->RTag��ʲô����һ�����һ����rchild
	}
	return OK;
}//PreTraverse_Thr

Status InTraverse_Thr(BiThrTree T, Status(*visit)(TElemType)) {
	//��������ǵݹ飬T���Ѿ���Threading�������������������
	BiThrNode* p = T->lchild;//��ʼָ����ڵ�
	while (p != T) {
		while (p->LTag == PointerTag::Link)
			p = p->lchild;
		if (!(*visit)(p->data)) return ERROR;
		while (p->RTag == PointerTag::Thread && p->rchild != T) {
			//������������ڴˣ���Linkʱrchild������һ��㣬��rchild��������Ѱ��ͷ���ǣ�
			//��ʱ��Ҫ����whileѭ������Threadʱ����Ҫѭ����ֱ��visit����������
			p = p->rchild;
			if (!(*visit)(p->data)) return ERROR;
		}
		p = p->rchild;
	}
	return OK;
}//InTraverse_Thr

Status PostTraverse_Thr(BiThrTree T, Status(*visit)(TElemType)) {
	//��������ǵݹ飬T���Ѿ���Threading�����������������������Ҫ�õ���������ṹ
	BiThrNode* p = T->lchild;//��ʼָ����ڵ�
	while (p != T) {
		while (p->LTag == PointerTag::Link || p->RTag == PointerTag::Link) {
			while (p->LTag == PointerTag::Link)
				p = p->lchild;
			if (p->RTag == PointerTag::Link)
				p = p->rchild;
		}
		if (!(*visit)(p->data)) return ERROR;
		while (p->RTag == PointerTag::Thread && p->rchild != T ||
			p->parent &&
			!(p->parent->LTag == PointerTag::Link && p->parent->RTag == PointerTag::Link && p == p->parent->lchild)) {
			//��while����������������while�������Ĳ���������á��ǡ���д����������ѭ������������
			while (p->RTag == PointerTag::Thread && p->rchild != T) {
				//������������ڴˣ���Linkʱrchild������һ��㣬��rchild��������Ѱ��ͷ���ǣ�
				//��ʱ��Ҫ����whileѭ������Threadʱ����Ҫѭ����ֱ��visit����������
				p = p->rchild;
				if (!(*visit)(p->data)) return ERROR;
			}
			if (p->parent &&
				(p == p->parent->rchild || p == p->parent->lchild && p->parent->RTag == PointerTag::Thread)) {
				//parent��p������������ʽ����������3�֣��������ֵ�p�ĺ�̶���p->parent
				//ע�⵱p->parent->lchild==pʱp��һ�������������ڵ㣬�п���parent->LTagΪthread����pΪ�����������ڵ�
				p = p->parent;
				if (!(*visit)(p->data)) return ERROR;
			}
		}
		if (!p->parent) p = T;//pΪ���ڵ㣬Ҳ�����һ�����
		else p = p->parent->rchild; //��ʱΪparent��p������ʽ�����һ��
	}
	return OK;
}//PostTraverse_Thr