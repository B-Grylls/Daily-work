#pragma once
# include <stdio.h>
# include <stdlib.h>
# include "visit.h"
# include "BiTree.h"
/*�����õ��������ṹ�ĵط���������ʱ�����޸�data�����ͣ�ֻ������ԭ��char�ͣ��洢�����ʱ��Ҳֻ�洢key��e.key�����洢��¼����e*/
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0

typedef int Status;
typedef char KeyType;
typedef struct STElemType {//һ������Ԫ�ػ��߼�¼
	KeyType key;//�ؼ�����
	int weight;//Ȩ����
	//���Բ��������ǹؼ�����
}STElemType;

/*��̬���ұ��˳���洢*/
typedef BiTree SOSTree;//Second Optimal Search Tree
typedef struct {
	STElemType* elem;
	int length;
}SSTable;

/*��̬���ұ�Ķ������洢*/
# define LH 1
# define RH -1
# define EH 0
typedef BiTree BSTree;//Binary Sort Tree����������,flag������bf��balance factor

/*�ȽϺ���*/

Status EQ(KeyType a, KeyType b);

Status LT(KeyType a, KeyType b);

Status LQ(KeyType a, KeyType b);

Status RT(KeyType a, KeyType b);

Status RQ(KeyType a, KeyType b);

/*��̬���ұ���*/

Status CreateSST(SSTable& ST);

Status DestroySST(SSTable& ST);

Status TraverseSST(SSTable& ST);

int Search_Seq(SSTable ST, KeyType key);

int Search_Bin(SSTable ST, KeyType key);

int Search_intpo(SSTable ST, KeyType key);

Status CreateSOSTree(SOSTree& T, SSTable ST, int sw[]);

Status SecondOptimal(BiTree& T, SSTable R, int sw[], int low, int high);

BiTNode* Search_SOSTree(SOSTree T, KeyType key);

/*��̬���ұ��������������*/

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



