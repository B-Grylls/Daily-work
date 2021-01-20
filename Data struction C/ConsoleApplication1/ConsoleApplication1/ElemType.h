#pragma once
typedef char TElemType;
typedef struct BiTNode {//二叉链表存储的二叉树
	TElemType data;
	BiTNode* lchild, * rchild;
	int flag;//此项专门用于非递归后序遍历函数
}BiTNode, * BiTree;
typedef BiTNode* SElemType;
typedef BiTNode* QElemType;
