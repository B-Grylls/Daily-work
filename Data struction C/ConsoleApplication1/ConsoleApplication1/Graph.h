#pragma once
# include <stdio.h>
# include <stdlib.h>
# include "visit.h"
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0
typedef int Status;

# define MAX_VERTEX_NUM 20 //��󶥵���
typedef char InfoType;//���廡�Ķ�����Ϣ����
typedef char VertexType;
enum class GraphKind { DG, DN, UDG, UDN };//����ͼ��������������ͼ��������
static bool visited[MAX_VERTEX_NUM];//DFS�õ��ķ��ʱ�־����
static Status(*VisitFunc)(char a);//DFS�õ���ȫ�ַ��ʺ���

/*ͼ�������ڽӾ���洢*/
# define INFINITY INT_MAX //���ֵ����
typedef int VRType;//��ʼ���嶥���ϵ�����ֱ�ʾ
typedef struct ArcCell {//�����
	VRType adj;//�����ϵ���ͣ���Ȩ����1/0��ʾ�Ƿ����ڣ���Ȩ����Ȩ�����ͱ�ʾ
	InfoType* info;//�û��������Ϣָ��
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {//ͼ/��
	VertexType vexs[MAX_VERTEX_NUM];//��Ŷ����һά����
	AdjMatrix arcs;//�ڽӾ���
	int vexnum, arcnum;//�����뻡��Ŀ
	GraphKind kind;//ͼ������
}MGraph;

/*ͼ���ڽӱ�洢*/
typedef struct ArcNode {//�����
	int adjvex;//�û���ָ��Ķ���λ��
	ArcNode* nextarc;//ָ����һ������ָ��
	InfoType* Info;//�û��������Ϣָ��
}ArcNode;
typedef struct VNode {//������
	VertexType data;//������Ϣ
	ArcNode* firstarc;//ָ���һ�������ڸö���Ļ�
}VNode;
typedef struct {//�ڽӱ�ͼ
	VNode vertices[MAX_VERTEX_NUM];//��ͷ����
	int vexnum, arcnum;//�����뻡��Ŀ
	GraphKind kind;//ͼ����
}ALGraph;

/*����ͼ��ʮ������洢*/
typedef struct ArcBox {//�����
	int tailvex, headvex;//�û���βͷ����λ��
	ArcBox* hlink, * tlink;//�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	InfoType* info;//������Ϣָ��
}ArcBox;
typedef struct VexNode {//������
	VertexType data;//������Ϣ
	ArcBox* firstin, * firstout;//�ֱ�ָ��ö���ĵ�һ���뻡�ͳ���
}VexNode;
typedef struct {//ʮ����������ͼ
	VexNode xlist[MAX_VERTEX_NUM];//��ͷ����
	int vexnum, arcnum;//����ͻ���Ŀ
}OLGraph;

/*����ͼ���ڽӶ��ر�洢*/
enum class VisitIf {unvisited,visited};
typedef struct EBox{//�߽��
	VisitIf mark;//��־���Ƿ񱻷��ʹ�
	int ivex, jvex;//�ñ����˵Ķ���λ��
	EBox* ilink, * jlink;//�ֱ�ָ��������i��j�������һ����
	InfoType* info;//�ߵ���Ϣָ��
}EBox;
typedef struct VexBox {//������
	VertexType data;//������Ϣ
	EBox* firstedge;//ָ�������ڸö����һ����
}VexBox;
typedef struct {//�ڽӶ��ر�����ͼ
	VexBox adjmulist[MAX_VERTEX_NUM];//��������
	int vexnum, arcnum;//����ͻ���Ŀ
}AMLGraph;

/*ͼ���ڽӾ���洢�µĻ�����������*/

Status CreateGraph(MGraph& G);

int LocateVex(MGraph G, char v);

Status CreateDG(MGraph& G);

Status CreateUDG(MGraph& G);

Status CreateDN(MGraph& G);

Status CreateUDN(MGraph& G);

Status DestroyGraph(MGraph& G);

int FirstAdjVex(MGraph G, char v);

int NextAdjVex(MGraph G, char v, char w);

Status InsertVex(MGraph& G, char v);

Status DeleteVex(MGraph& G, char v);

Status InsertArc(MGraph& G, char v, char w);

Status InsertArc(MGraph& G, char v, char w, int weight);

Status DeleteArc(MGraph& G, char v, char w);

/*ͼ���ڽӱ�洢�µĻ�����������*/

Status CreateGraph(ALGraph& G);

int LocateVex(ALGraph& G, char v);

Status DestroyGraph(ALGraph& G);

int FirstAdjVex(ALGraph G, char v);

int NextAdjVex(ALGraph G, char v, char w);

Status InsertVex(ALGraph& G, char v);

Status DeleteVex(ALGraph& G, char v);

Status InsertArc(ALGraph& G, char v, char w);

Status DeleteArc(ALGraph& G, char v, char w);

/*����ͼ��ʮ������洢�µĻ�������*/

Status CreateGraph(OLGraph& G);

int LocateVex(OLGraph G, char v);

Status DestroyGraph(OLGraph& G);

int FirstOutVex(OLGraph G, char v);

int FirstInVex(OLGraph G, char v);

int NextOutVex(OLGraph G, char v, char w);

int NextInVex(OLGraph G, char v, char w);

Status InsertVex(OLGraph& G, char v);

Status DeleteVex(OLGraph& G, char v);

Status InsertArc(OLGraph& G, char v, char w);

Status DeleteArc(OLGraph& G, char v, char w);

/*����ͼ���ڽӶ��ر�洢�µĻ�������*/

Status CreateGraph(AMLGraph& G);

int LocateVex(AMLGraph G, char v);

Status DestroyGraph(AMLGraph& G);

int FirstAdjVex(AMLGraph G, char v);

int NextAdjVex(AMLGraph G, char v, char w);

Status InsertVex(AMLGraph& G, char v);

Status DeleteVex(AMLGraph& G, char v);

Status InsertEdge(AMLGraph& G, char v, char w);

Status DeleteEdge(AMLGraph& G, char v, char w);

/*ͼ�����ֱ���*/

Status DFSTraverse(MGraph G, Status(*visit)(char a));

Status DFS(MGraph G, int i);

Status DFSTraverse(ALGraph G, Status(*visit)(char a));

Status DFS(ALGraph G, int i);

Status DFSTraverse(OLGraph G, Status(*visit)(char a));

Status DFS(OLGraph G, int i);

Status DFSTraverse(AMLGraph G, Status(*visit)(char a));

Status DFS(AMLGraph G, int i);
