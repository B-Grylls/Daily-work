#pragma once
# include <stdio.h>
# include <stdlib.h>
# include "visit.h"
# include "BiTree.h"
/*下述用到二叉树结构的地方，由于暂时不会修改data域类型，只能暂用原定char型，存储有序表时，也只存储key域e.key而不存储记录整体e*/
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0

typedef int Status;
typedef char KeyType;
typedef struct STElemType {//一个数据元素或者记录
	KeyType key;//关键字域
	int weight;//权重域
	//可以补充其他非关键字域
}STElemType;

/*静态查找表的顺序表存储*/
typedef BiTree SOSTree;//Second Optimal Search Tree
typedef struct {
	STElemType* elem;
	int length;
}SSTable;

/*动态查找表的二叉树存储*/
# define LH 1
# define RH -1
# define EH 0
typedef BiTree BSTree;//Binary Sort Tree二叉排序树,flag域用作bf域balance factor

/*比较函数*/

Status EQ(KeyType a, KeyType b);

Status LT(KeyType a, KeyType b);

Status LQ(KeyType a, KeyType b);

Status RT(KeyType a, KeyType b);

Status RQ(KeyType a, KeyType b);

/*静态查找表函数*/

Status CreateSST(SSTable& ST);

Status DestroySST(SSTable& ST);

Status TraverseSST(SSTable& ST);

int Search_Seq(SSTable ST, KeyType key);

int Search_Bin(SSTable ST, KeyType key);

int Search_intpo(SSTable ST, KeyType key);

Status CreateSOSTree(SOSTree& T, SSTable ST, int sw[]);

Status SecondOptimal(BiTree& T, SSTable R, int sw[], int low, int high);

BiTNode* Search_SOSTree(SOSTree T, KeyType key);

/*动态查找表二叉排序树函数*/

Status InitBST(BSTree& T);

Status DestroyBST(BSTree& T);

Status SearchBST(BSTree T, KeyType key, BiTNode* f, BiTNode*& p);

Status InsertBST(BSTree& T, STElemType e);

Status DeleteBST(BSTree& T, KeyType key);

Status DeleteBSNode(BiTNode*& p);

Status InsertAVL(BSTree& T, STElemType e, bool& taller);

Status LeftBalance(BSTree& T);

Status RightBalance(BSTree& T);

Status R_Rotate(BSTree& p);

Status L_Rotate(BSTree& p);



