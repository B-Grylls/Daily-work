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

# define MAX_VERTEX_NUM 20 //最大顶点数
typedef char InfoType;//定义弧的额外信息类型
typedef char VertexType;
enum class GraphKind { DG, DN, UDG, UDN };//有向图，有向网，无向图，无向网
static bool visited[MAX_VERTEX_NUM];//DFS用到的访问标志数组
static Status(*VisitFunc)(char a);//DFS用到的全局访问函数

/*图或网的邻接矩阵存储*/
# define INFINITY INT_MAX //最大值无穷
typedef int VRType;//初始定义顶点关系用数字表示
typedef struct ArcCell {//弧结点
	VRType adj;//顶点关系类型，无权则用1/0表示是否相邻，有权则用权的类型表示
	InfoType* info;//该弧的相关信息指针
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {//图/网
	VertexType vexs[MAX_VERTEX_NUM];//存放顶点的一维数组
	AdjMatrix arcs;//邻接矩阵
	int vexnum, arcnum;//顶点与弧数目
	GraphKind kind;//图的类型
}MGraph;

/*图的邻接表存储*/
typedef struct ArcNode {//弧结点
	int adjvex;//该弧所指向的顶点位置
	ArcNode* nextarc;//指向下一条弧的指针
	InfoType* Info;//该弧的相关信息指针
}ArcNode;
typedef struct VNode {//顶点结点
	VertexType data;//顶点信息
	ArcNode* firstarc;//指向第一条依附于该顶点的弧
}VNode;
typedef struct {//邻接表图
	VNode vertices[MAX_VERTEX_NUM];//表头向量
	int vexnum, arcnum;//顶点与弧数目
	GraphKind kind;//图类型
}ALGraph;

/*有向图的十字链表存储*/
typedef struct ArcBox {//弧结点
	int tailvex, headvex;//该弧的尾头顶点位置
	ArcBox* hlink, * tlink;//分别为弧头相同和弧尾相同的弧的链域
	InfoType* info;//弧的信息指针
}ArcBox;
typedef struct VexNode {//顶点结点
	VertexType data;//顶点信息
	ArcBox* firstin, * firstout;//分别指向该顶点的第一条入弧和出弧
}VexNode;
typedef struct {//十字链表有向图
	VexNode xlist[MAX_VERTEX_NUM];//表头向量
	int vexnum, arcnum;//顶点和弧数目
}OLGraph;

/*无向图的邻接多重表存储*/
enum class VisitIf {unvisited,visited};
typedef struct EBox{//边结点
	VisitIf mark;//标志域，是否被访问过
	int ivex, jvex;//该边两端的顶点位置
	EBox* ilink, * jlink;//分别指向依附于i或j顶点的下一条边
	InfoType* info;//边的信息指针
}EBox;
typedef struct VexBox {//顶点结点
	VertexType data;//顶点信息
	EBox* firstedge;//指向依附于该顶点第一条边
}VexBox;
typedef struct {//邻接多重表无向图
	VexBox adjmulist[MAX_VERTEX_NUM];//顶点向量
	int vexnum, arcnum;//顶点和弧数目
}AMLGraph;

/*图的邻接矩阵存储下的基本操作函数*/

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

/*图的邻接表存储下的基本操作函数*/

Status CreateGraph(ALGraph& G);

int LocateVex(ALGraph& G, char v);

Status DestroyGraph(ALGraph& G);

int FirstAdjVex(ALGraph G, char v);

int NextAdjVex(ALGraph G, char v, char w);

Status InsertVex(ALGraph& G, char v);

Status DeleteVex(ALGraph& G, char v);

Status InsertArc(ALGraph& G, char v, char w);

Status DeleteArc(ALGraph& G, char v, char w);

/*有向图的十字链表存储下的基本函数*/

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

/*无向图的邻接多重表存储下的基本函数*/

Status CreateGraph(AMLGraph& G);

int LocateVex(AMLGraph G, char v);

Status DestroyGraph(AMLGraph& G);

int FirstAdjVex(AMLGraph G, char v);

int NextAdjVex(AMLGraph G, char v, char w);

Status InsertVex(AMLGraph& G, char v);

Status DeleteVex(AMLGraph& G, char v);

Status InsertEdge(AMLGraph& G, char v, char w);

Status DeleteEdge(AMLGraph& G, char v, char w);

/*图的两种遍历*/

Status DFSTraverse(MGraph G, Status(*visit)(char a));

Status DFS(MGraph G, int i);

Status DFSTraverse(ALGraph G, Status(*visit)(char a));

Status DFS(ALGraph G, int i);

Status DFSTraverse(OLGraph G, Status(*visit)(char a));

Status DFS(OLGraph G, int i);

Status DFSTraverse(AMLGraph G, Status(*visit)(char a));

Status DFS(AMLGraph G, int i);
