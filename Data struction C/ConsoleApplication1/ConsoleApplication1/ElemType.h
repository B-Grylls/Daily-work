#pragma once
typedef char TElemType;
typedef struct BiTNode {//��������洢�Ķ�����
	TElemType data;
	BiTNode* lchild, * rchild;
	int flag;//����ר�����ڷǵݹ�����������
}BiTNode, * BiTree;
typedef BiTNode* SElemType;
typedef BiTNode* QElemType;
