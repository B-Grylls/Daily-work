#pragma once
# include "Stack.h"
# include "Queue.h"
# include <stdio.h>
# include <stdlib.h>
# include "visit.h"
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0

typedef int Status;
/*���涨�����Stack ElemType.h�У�Ϊ�˿����ڶ����������е���ջ*/
typedef char TElemType;
/*typedef struct BiTNode {//��������洢�Ķ�����
	TElemType data;
	BiTNode* lchild, * rchild;
	int flag;//����ר�����ڷǵݹ�����������
}BiTNode, * BiTree;*/

enum class PointerTag { Thread,Link };
typedef struct BiThrNode {//����������
	TElemType data;
	BiThrNode* lchild, * rchild;
	PointerTag LTag, RTag;//��־��
	BiThrNode* parent;//����ר�����ں����������������ʱ��Ҫ����������
}BiThrNode,*BiThrTree;

Status InitBiTree(BiTree& T);

Status CreateBiTree(BiTree& T);

Status DestroyBiTree(BiTree& T);

Status ClearBiTree(BiTree& T);

Status BiTreeEmpty(BiTree T);

Status CopyBiTree(BiTree T, BiTree& S);

Status CopyBiTree_nrc1(BiTree T, BiTree& S);

Status CopyBiTree_nrc2(BiTree T, BiTree& S);

int BiTreeDepth(BiTree T);

BiTNode* Root(BiTree T);

TElemType Value(BiTree T, BiTNode* e);

Status Assign(BiTree& T, BiTNode* e, TElemType value);

BiTNode* Parent(BiTree T, BiTNode* e);

BiTNode* LeftChild(BiTree T, BiTNode* e);

BiTNode* RightChild(BiTree T, BiTNode* e);

BiTNode* LeftSibling(BiTree T, BiTNode* e);

BiTNode* RightSibling(BiTree T, BiTNode* e);

Status InsertChild(BiTree& T, BiTNode* p, int LR, BiTree& C);

Status DeleteChild(BiTree& T, BiTNode* p, int LR);

Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType));

Status InOrderTraverse(BiTree T, Status(*visit)(TElemType));

Status AntiInOrderPrint(BiTree T, int depth);

Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType));

Status LevelOrderTraverse(BiTree T, Status(*visit)(TElemType));

/*3�ֱ�����2�ַǵݹ���ʽ*/

Status PreTraverse(BiTree T, Status(*visit)(TElemType));

Status PreOrder(BiTree T, Status(*visit)(TElemType));

Status InTraverse(BiTree T, Status(*visit)(TElemType));

Status InOrder(BiTree T, Status(*visit)(TElemType));

Status PostTraverse(BiTree T, Status(*visit)(TElemType));

Status PostOrder(BiTree T, Status(*visit)(TElemType));

/*�����������ı�������*/

Status CreatBiThrTree(BiThrTree& T);

Status DestroyBiThrTree(BiThrTree& T);

Status Threading(BiThrTree& Thrt, BiThrTree T, Status(*OrderThreading)(BiThrTree&, BiThrTree));

Status PreThreading(BiThrTree& pre, BiThrTree p);

Status InThreading(BiThrTree& pre, BiThrTree p);

Status PostThreading(BiThrTree& pre, BiThrTree p);

Status PreTraverse_Thr(BiThrTree T, Status(*visit)(TElemType));

Status InTraverse_Thr(BiThrTree T, Status(*visit)(TElemType));

Status PostTraverse_Thr(BiThrTree T, Status(*visit)(TElemType));
