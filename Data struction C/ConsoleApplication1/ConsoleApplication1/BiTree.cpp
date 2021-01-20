# include"BiTree.h"



Status InitBiTree(BiTree& T) {
	//初始化一个空的二叉树
	T = NULL;
	return OK;
}//InitBiTree

Status CreateBiTree(BiTree& T) {
	//先序次序输入结点，空格字符表示空树
	//注意字符需要一次性输入，否则scanf就会重复读取回车
	char ch;
	scanf_s("%c", &ch);
	if (ch == ' ') T = NULL;
	else {
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = ch;
		T->flag = 0;//该项仅为非递归后序遍历服务
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}//CreatBiTree

Status DestroyBiTree(BiTree& T) {
	//销毁一个二叉树
	if (!T) return OK;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
	T = NULL;
	return OK;
}//DestroyBiTree

Status ClearBiTree(BiTree& T) {
	//清空二叉树
	if (!T) return OK;
	ClearBiTree(T->lchild);
	ClearBiTree(T->rchild);
	free(T);
	T = NULL;
	return OK;
}//ClearBiTree

Status BiTreeEmpty(BiTree T) {
	//判别二叉树是否为空
	if (!T) return TRUE;
	else return FALSE;
}//BiTreeEmpty

Status CopyBiTree(BiTree T, BiTree& S) {
	//二叉树T复制给S，递归算法
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
	//二叉树T复制给S，非递归算法，利用栈
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
	//二叉树T复制给S，非递归算法，利用栈
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
	//返回树的深度
	if (!T) return 0;
	int a = BiTreeDepth(T->lchild);
	int b = BiTreeDepth(T->rchild);
	int max = a > b ? a : b;
	return max + 1;
}//BiTreeDepth

BiTNode* Root(BiTree T) {
	//返回二叉树T的根
	return T;
}//Root

TElemType Value(BiTree T, BiTNode* e) {
	//返回树T中结点e的值
	return e->data;
}//Value

Status Assign(BiTree& T, BiTNode* e, TElemType value) {
	//将值value赋给二叉树T中结点e
	e->data = value;
	return OK;
}//Assign

BiTNode* Parent(BiTree T, BiTNode* e) {
	//返回二叉树T中结点e的parent，若无返回NULL
	if (T == e) return NULL;
	if (!T) return NULL;
	if (T->lchild == e || T->rchild == e) return T;
	BiTNode* node;
	if (node = Parent(T->lchild, e))
		return node;
	else return Parent(T->rchild, e);
}//Parent

BiTNode* LeftChild(BiTree T, BiTNode* e) {
	//返回结点e的左child，若无返回NULL
	return e->lchild;
}//LeftChild

BiTNode* RightChild(BiTree T, BiTNode* e) {
	//返回结点e的右child，若无返回NULL
	return e->rchild;
}//RightChild

BiTNode* LeftSibling(BiTree T, BiTNode* e) {
	//返回结点e的左sibling，若无返回NULL
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
	//返回结点e的右sibling，若无返回NULL
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
	//p为二叉树T中某个结点，C为非空二叉树，与T不相交，右子树为空
	//LR=0||1表示将C插入到p的左或右子树位置，替换下的子树接在C的右子树位置上
	if (!C || C->rchild) return ERROR;
	BiTNode* node;
	if (LR == 0) {//C插入p的左子树位置
		node = p->lchild;
		p->lchild = C;
	}
	else {//C插入p的右子树位置
		node = p->rchild;
		p->rchild = C;
	}
	C->rchild = node;
	return OK;
}//InsertChild

Status DeleteChild(BiTree& T, BiTNode* p, int LR) {
	//p为二叉树T中的结点，删除p的左（LR=0）或右（LR=1）子树
	if (LR == 0) DestroyBiTree(p->lchild);
	else DestroyBiTree(p->rchild);
	return OK;
}//DeleteChild

Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType)) {
	//先序遍历
	if (!T) return OK;
	if (!(*visit)(T->data)) return ERROR;
	if (!PreOrderTraverse(T->lchild, (*visit))) return ERROR;
	if (!PreOrderTraverse(T->rchild, (*visit))) return ERROR;
	return OK;
}//PreOrderTraverse

Status InOrderTraverse(BiTree T, Status(*visit)(TElemType)) {
	//中序遍历
	if (!T) return OK;
	if (!InOrderTraverse(T->lchild, (*visit))) return ERROR;
	if (!(*visit)(T->data)) return ERROR;
	if (!InOrderTraverse(T->rchild, (*visit))) return ERROR;
	return OK;
}//InOrderTraverse

Status AntiInOrderPrint(BiTree T, int depth = 1) {
	//反向中序遍历，且横向打印出树的形状
	if (!T) return OK;
	if (!AntiInOrderPrint(T->rchild, depth + 1)) return ERROR;
	for (int i = 1; i < depth; ++i)
		printf(" ");
	printf("%c\n", T->data);
	if (!AntiInOrderPrint(T->lchild, depth + 1)) return ERROR;
	return OK;
}//AntiInOrderPrint

Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType)) {
	//后序遍历
	if (!T) return OK;
	if (!PostOrderTraverse(T->lchild, (*visit))) return ERROR;
	if (!PostOrderTraverse(T->rchild, (*visit))) return ERROR;
	if (!(*visit)(T->data)) return ERROR;
	return OK;
}//PostOrderTraverse

Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType)) {
	//层序遍历，非递归，利用队列
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

/*3种遍历的2种非递归形式*/
/*2种非递归区别在于，对于当前研究结点，是直接入栈然后GetTop(S,p)再对p做详细判断，还是用指针p指向它，
做完详细判断后，再看是否入栈，明显标志区别在于NULL时前者会push null入栈，再pop出来，而后者不会入栈*/
//已提前在头文件中将栈的基本元素类型设置为BiTNode*
Status PreTraverse(BiTree T, Status(*visit)(TElemType)) {
	//先序遍历非递归
	LinkStack S;
	InitStack(S);
	Push(S, T);
	BiTNode* p;
	while (!StackEmpty(S)) {
		while (GetTop(S, p) && p) {
			if (!(*visit)(p->data)) return ERROR;
			Push(S, p->lchild);
		}
		Pop(S, p);//去NULL
		if (!StackEmpty(S)) {
			Pop(S, p);
			Push(S, p->rchild);
		}
	}
	return OK;
}//PreTraverse

Status PreOrder(BiTree T, Status(*visit)(TElemType)) {
	//先序遍历非递归
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
	//中序遍历非递归
	LinkStack S;
	InitStack(S);
	Push(S, T);
	BiTNode* p;
	while (!StackEmpty(S)) {
		while (GetTop(S, p) && p)
			Push(S, p->lchild);
		Pop(S, p);//去NULL
		if (!StackEmpty(S)) {
			Pop(S, p);
			if (!(*visit)(p->data)) return ERROR;
			Push(S, p->rchild);
		}
	}
	return OK;
}//InTraverse

Status InOrder(BiTree T, Status(*visit)(TElemType)) {
	//中序遍历非递归
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
	//后序遍历非递归，此时需要用到定义中的flag
	LinkStack S;
	InitStack(S);
	Push(S, T);
	BiTNode* p;
	while (!StackEmpty(S)) {
		while (GetTop(S, p) && p)
			if (!p->lchild || p->lchild->flag == 0)
				Push(S, p->lchild);
			else Push(S, NULL);
		Pop(S, p);//去NULL
		if (!StackEmpty(S)) {
			GetTop(S, p);
			if (p->flag == 1) {//当该结点是从其rchild返回时再输出
				Pop(S, p);
				if (!(*visit)(p->data)) return ERROR;
			}
			else {
				p->flag = 1;
				Push(S, p->rchild);//当该结点从其lchild返回时先处理rchild
			}
		}
	}
	return OK;
}//PostTraverse

Status PostOrder(BiTree T, Status(*visit)(TElemType)) {
	//后序遍历非递归
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

/*线索二叉树的遍历函数*/

Status CreatBiThrTree(BiThrTree& T) {
	//先序次序输入结点，空格字符表示空树
	//注意字符需要一次性输入，否则scanf就会重复读取回车
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
	//销毁一个二叉线索树
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
	//Thrt头结点，按(*OrderThreading)的顺序线索化二叉树T
	Thrt = (BiThrNode*)malloc(sizeof(BiThrNode));
	if (!Thrt) exit(OVERFLOW);
	Thrt->LTag = PointerTag::Link;
	Thrt->RTag = PointerTag::Thread;
	Thrt->rchild = Thrt;//右指针回指
	if (!T) Thrt->lchild = Thrt;//T空则头结点左指针回指
	else {
		BiThrNode* pre = Thrt;
		Thrt->lchild = T;
		(*OrderThreading)(pre, T);//先序/中序/后序 线索化树T
		Thrt->rchild = pre;
		if (!pre->rchild)
			pre->rchild = Thrt;
	}
	return OK;
}//Threading

Status PreThreading(BiThrTree& pre, BiThrTree p) {
	//先序线索化二叉树T，做函数Threading的函数参数
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
	if (p->LTag == PointerTag::Link)//p->lchild如果在前面被更改了，说明其左子树为空，直接跳过
		PreThreading(pre, p->lchild);
	if (p->RTag == PointerTag::Link)
		PreThreading(pre, p->rchild);
	return OK;
}//PreThreading

Status InThreading(BiThrTree& pre, BiThrTree p) {
	//中序线索化二叉树T，做函数Threading的函数参数
	if (!p) return OK;
	InThreading(pre, p->lchild);//与先序线索化不同，p->lchild一定未被更改，所以不用判别Tag
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
	//后序线索化二叉树T，做函数Threading的函数参数
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
	//先序遍历非递归，T是已经用Threading线索化后的线索二叉树
	BiThrNode* p = T->lchild;//初始指向根节点
	while (p != T) {
		if (!(*visit)(p->data)) return ERROR;
		while (p->LTag == PointerTag::Link) {
			p = p->lchild;
			if (!(*visit)(p->data)) return ERROR;
		}
		p = p->rchild;//此时不论p->RTag是什么，下一个结点一定是rchild
	}
	return OK;
}//PreTraverse_Thr

Status InTraverse_Thr(BiThrTree T, Status(*visit)(TElemType)) {
	//中序遍历非递归，T是已经用Threading线索化后的线索二叉树
	BiThrNode* p = T->lchild;//初始指向根节点
	while (p != T) {
		while (p->LTag == PointerTag::Link)
			p = p->lchild;
		if (!(*visit)(p->data)) return ERROR;
		while (p->RTag == PointerTag::Thread && p->rchild != T) {
			//与先序的区别在此，当Link时rchild不是下一结点，而rchild再向左搜寻到头才是，
			//此时需要上面while循环，而Thread时不需要循环，直接visit，继续步骤
			p = p->rchild;
			if (!(*visit)(p->data)) return ERROR;
		}
		p = p->rchild;
	}
	return OK;
}//InTraverse_Thr

Status PostTraverse_Thr(BiThrTree T, Status(*visit)(TElemType)) {
	//后序遍历非递归，T是已经用Threading线索化后的线索二叉树，需要用到三叉链表结构
	BiThrNode* p = T->lchild;//初始指向根节点
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
			//此while的条件即下面两个while的条件的并，这里采用“非”的写法方便跳出循环后的情况考虑
			while (p->RTag == PointerTag::Thread && p->rchild != T) {
				//与先序的区别在此，当Link时rchild不是下一结点，而rchild再向左搜寻到头才是，
				//此时需要上面while循环，而Thread时不需要循环，直接visit，继续步骤
				p = p->rchild;
				if (!(*visit)(p->data)) return ERROR;
			}
			if (p->parent &&
				(p == p->parent->rchild || p == p->parent->lchild && p->parent->RTag == PointerTag::Thread)) {
				//parent与p存在有四种形式，这是其中3种，而这三种的p的后继都是p->parent
				//注意当p->parent->lchild==p时p不一定是左子树根节点，有可能parent->LTag为thread，而p为其右子树根节点
				p = p->parent;
				if (!(*visit)(p->data)) return ERROR;
			}
		}
		if (!p->parent) p = T;//p为根节点，也是最后一个结点
		else p = p->parent->rchild; //此时为parent与p四种形式的最后一种
	}
	return OK;
}//PostTraverse_Thr