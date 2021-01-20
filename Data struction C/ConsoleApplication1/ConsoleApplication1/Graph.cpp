# include "Graph.h"

/*图的邻接矩阵存储下的基本操作函数*/

Status CreateGraph(MGraph& G) {
	//邻接矩阵法创建图G
	printf("输入图的类型：有向图0，有向网1，无向图2，无向网3:\n");
	scanf_s("%d", &G.kind);//0-3分别代表DG,DN,UDG,UDN
	switch (G.kind) {
	case GraphKind::DG: return CreateDG(G);
	case GraphKind::DN: return CreateDN(G);
	case GraphKind::UDG: return CreateUDG(G);
	case GraphKind::UDN: return CreateUDN(G);
	default: return ERROR;
	}
}//CreateGraph

int LocateVex(MGraph G, char v) {
	//确定顶点v在图顶点数组中的下标
	for (int i = 0; i < G.vexnum; ++i)
		if (G.vexs[i] == v) return i;
	return -1;
}//LocateVex

Status CreateDG(MGraph& G) {
	//构造有向图G
	int IncInfo;
	printf("依次输入顶点数，弧数，弧有无额外信息0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfo为0时，弧不含其他信息
	getchar();//清除换行符
	for (int i = 0; i < G.vexnum; ++i) scanf_s("%c", &G.vexs[i]);//构造顶点数组
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			G.arcs[i][j] = { 0,NULL };//邻接矩阵初始化
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//输入该边的两顶点，有序
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
		if (IncInfo);//Input(*G.arcs[i][j].info);
	}
	return OK;
}//CreateDG

Status CreateUDG(MGraph& G) {
	//构造无向图G
	int IncInfo;
	printf("依次输入顶点数，弧数，弧有无额外信息0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfo为0时，弧不含其他信息
	getchar();//清除换行符
	for (int i = 0; i < G.vexnum; ++i) scanf_s("%c", &G.vexs[i], 1);//构造顶点数组
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			G.arcs[i][j] = { 0,NULL };//邻接矩阵初始化
	for (int i = G.vexnum; i < MAX_VERTEX_NUM; ++i) G.vexs[i] = 0;
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//输入该边的两顶点
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
		if (IncInfo);//Input(*G.arcs[i][j].info);
		G.arcs[j][i] = G.arcs[i][j];
	}
	return OK;
}//CreateUDG

Status CreateDN(MGraph& G) {
	//构造无向网G
	int IncInfo;
	printf("依次输入顶点数，弧数，弧有无额外信息0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfo为0时，弧不含其他信息
	getchar();//清除换行符
	for (int i = 0; i < G.vexnum; ++i) scanf_s("%c", &G.vexs[i]);//构造顶点数组
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			G.arcs[i][j] = { INFINITY,NULL };//邻接矩阵初始化
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		int weight;
		scanf_s(" %c %c %d", &v1, 1, &v2, 1, &weight);//输入该边的两顶点及权重
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = weight;
		if (IncInfo);//Input(*G.arcs[i][j].info);
	}
	return OK;
}//CreateDN

Status CreateUDN(MGraph& G) {
	//构造无向网G
	int IncInfo;
	printf("依次输入顶点数，弧数，弧有无额外信息0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfo为0时，弧不含其他信息
	getchar();//清除换行符
	for (int i = 0; i < G.vexnum; ++i) scanf_s("%c", &G.vexs[i]);//构造顶点数组
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			G.arcs[i][j] = { INFINITY,NULL };//邻接矩阵初始化
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		int weight;
		scanf_s(" %c %c %d", &v1, 1, &v2, 1, &weight);//输入该边的两顶点及权重
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = weight;
		if (IncInfo);//Input(*G.arcs[i][j].info);
		G.arcs[j][i] = G.arcs[i][j];
	}
	return OK;
}//CreateUDN

Status DestroyGraph(MGraph& G) {
	//销毁图G
	//G中的元素包括一维和二维数组都是栈上的内存会自动释放
	return OK;
}//DestroyGraph

int FirstAdjVex(MGraph G, char v) {
	//返回无向图G中顶点v的第一个邻接顶点，若无则返回空
	//有向图为出弧的邻接顶点，下同
	//注意返回邻接顶点返回的都是位置，类似函数均同
	int i = LocateVex(G, v);
	for (int j = 0; j < G.vexnum; ++j)
		if (G.arcs[i][j].adj == 1)
			return j;
	return -1;
}//FirstAdjvex

int NextAdjVex(MGraph G, char v, char w) {
	//无向图G，w为v的邻接顶点，返回v的下一个邻接顶点，若w为最后一个，返回空
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	for (int k = j + 1; k < G.vexnum; ++k)
		if (G.arcs[i][k].adj == 1)
			return k;
	return -1;
}//NextAdjVex

Status InsertVex(MGraph& G, char v) {
	//在图或网G中增添新结点v
	if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;//内存已满
	G.vexs[G.vexnum] = v;
	G.vexnum++;
	return OK;
}//InsertVex

Status DeleteVex(MGraph& G, char v) {
	//删除图或网G中的顶点v，以及相关的弧
	int i = LocateVex(G, v);
	for (int j = i; j < G.vexnum - 1; ++j) G.vexs[j] = G.vexs[j + 1];
	int arc = 0;//与v有关系的弧数
	for (int j = 0; j < G.vexnum; ++j) {
		if (G.kind == GraphKind::DG)//有向图
			if (G.arcs[i][j].adj == 1) arc++;
		if (G.kind == GraphKind::DN)//有向网
			if (G.arcs[i][j].adj != INFINITY) arc++;
		if (G.kind == GraphKind::UDG)//无向图
			if (G.arcs[i][j].adj == 1) arc++;
		if (G.kind == GraphKind::UDN)//无向网
			if (G.arcs[i][j].adj != INFINITY) arc++;
	}
	if (G.kind == GraphKind::DG || G.kind == GraphKind::DN) {//有向也需要计算列
		for (int j = 0; j < G.vexnum; ++j) {
			if (G.kind == GraphKind::DG)//有向图
				if (G.arcs[j][i].adj == 1) arc++;
			if (G.kind == GraphKind::DN)//有向网
				if (G.arcs[j][i].adj != INFINITY) arc++;
		}
	}
	//接下来删除二维数组的i行和i列
	for (int j = 1; j < G.vexnum; ++j) {//删除i行
		for (int k = i; k < G.vexnum - 1; ++k)
			G.arcs[k][j] = G.arcs[k + 1][j];
	}
	for (int j = 1; j < G.vexnum; ++j) {//删除i列
		for (int k = i; k < G.vexnum - 1; ++k)
			G.arcs[j][k] = G.arcs[j][k + 1];
	}
	G.arcnum -= arc;
	G.vexnum--;
	return OK;
}//DeleteVex

Status InsertArc(MGraph& G, char v, char w) {
	//向图G中增添弧<v,w>，若图无向，同时增加对称的<w,v>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	if (G.arcs[i][j].adj == 0) G.arcnum++;//此时边不存在
	G.arcs[i][j].adj = 1;
	if (G.kind == GraphKind::UDG)
		G.arcs[j][i].adj = 1;
	return OK;
}//InsertArc

Status InsertArc(MGraph& G, char v, char w, int weight) {
	//向网G中增添弧<v,w>，权重为weight，若图无向，同时增加对称的<w,v>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	if (G.arcs[i][j].adj == INFINITY) G.arcnum++;//此时边不存在
	G.arcs[i][j].adj = weight;
	if (G.kind == GraphKind::UDN)
		G.arcs[j][i].adj = weight;
	return OK;
}//InsertArc

Status DeleteArc(MGraph& G, char v, char w) {
	//删除图或网G中的弧<v,w>，如果图无向，同时删除弧<w,v>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	switch (G.kind) {
	case GraphKind::DG:
		if (G.arcs[i][j].adj != 0) --G.arcnum;
		G.arcs[i][j].adj = 0;
		break;
	case GraphKind::DN:
		if (G.arcs[i][j].adj != INFINITY) --G.arcnum;
		G.arcs[i][j].adj = INFINITY;
		break;
	case GraphKind::UDG:
		if (G.arcs[i][j].adj != 0) --G.arcnum;
		G.arcs[i][j].adj = G.arcs[j][i].adj = 0;
		break;
	case GraphKind::UDN:
		if (G.arcs[i][j].adj != INFINITY) --G.arcnum;
		G.arcs[i][j].adj = G.arcs[j][i].adj = INFINITY;
		break;
	}
	return OK;
}//DeleteArc

/*图的邻接表存储下的基本操作函数*/

Status CreateGraph(ALGraph& G) {
	//邻接表法创建图G
	printf("输入图的类型：有向图0，无向图2:\n");
	scanf_s("%d", &G.kind);//0和2分别代表DG,UDG
	int IncInfo;
	printf("依次输入顶点数，弧数，弧有无额外信息0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfo为0时，弧不含其他信息
	getchar();
	for (int i = 0; i < G.vexnum; ++i) {
		scanf_s("%c", &G.vertices[i].data);//构造顶点数组
		G.vertices[i].firstarc = NULL;
	}
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//输入该边的两顶点，有序
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		if (!p) return ERROR;
		p->adjvex = j;
		p->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p;//头插
		if (IncInfo);//Input(*p->Info);
		if (G.kind == GraphKind::UDG) {//无向图时对称操作
			ArcNode* q = (ArcNode*)malloc(sizeof(ArcNode));
			if (!q) return ERROR;
			q->adjvex = i;
			q->Info = p->Info;
			q->nextarc = G.vertices[j].firstarc;
			G.vertices[j].firstarc = q;
		}
	}
	return OK;
}//CreateGraph

int LocateVex(ALGraph& G, char v) {
	//查找顶点v在图G中的位置
	for (int i = 0; i < G.vexnum; ++i)
		if (G.vertices[i].data == v)
			return i;
	return -1;
}//LocateVex

Status DestroyGraph(ALGraph& G) {
	//销毁邻接表图G
	ArcNode* p, * pre;
	for (int i = 0; i < G.vexnum; ++i) {
		p = G.vertices[i].firstarc;
		pre = NULL;
		while (p) {
			pre = p;
			p = p->nextarc;
			free(pre);
		}
		G.vertices[i].firstarc = NULL;
	}
	return OK;
}//DestroyGraph

int FirstAdjVex(ALGraph G, char v) {
	//返回图G中v的第一个邻接顶点，对于有向图返回的是邻接自v的
	//对于邻接到v的顶点，需要遍历全体寻找
	int i = LocateVex(G, v);
	if (!G.vertices[i].firstarc) return -1;//无邻接
	return G.vertices[i].firstarc->adjvex;
}//FirstAdjVex

int NextAdjVex(ALGraph G, char v, char w) {
	//返回图G中v的邻接顶点中的w的下一个顶点，对于有向图返回的是邻接自v的
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcNode* p = G.vertices[i].firstarc;
	while (p && p->adjvex != j)
		p = p->nextarc;
	if (!p) return -1;
	if (!p->nextarc) return -1;
	return p->nextarc->adjvex;
}//NextAdjVex

Status InsertVex(ALGraph& G, char v) {
	//在图G中添加顶点v
	if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;//顶点已满
	G.vertices[G.vexnum].data = v;
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
	return OK;
}//InsertVex

Status DeleteVex(ALGraph& G, char v) {
	//删除图G中的顶点v以及依附于其的弧
	int arc = 0;//记录删去的弧数e
	int i = LocateVex(G, v);
	ArcNode* p, * pre;
	p = G.vertices[i].firstarc;
	pre = NULL;
	while (p) {
		pre = p; p = p->nextarc; free(pre); arc++;
	}
	for (int j = i; j < G.vexnum - 1; ++j) {//后续顶点前缩
		G.vertices[j].data = G.vertices[j + 1].data;
		G.vertices[j].firstarc = G.vertices[j + 1].firstarc;
	}
	G.vertices[G.vexnum - 1].firstarc = NULL;
	G.vexnum--;
	for (int j = 0; j < G.vexnum; ++j) {//遍历所有结点，删除邻接到v的弧结点，且将关于前缩顶点的位置值都减1
		p = G.vertices[j].firstarc; pre = NULL;
		while (p && p->adjvex == i) {//头结点类型与弧结点不一样，不能利用pre来删除
			G.vertices[j].firstarc = p->nextarc;
			free(p);
			p = G.vertices[j].firstarc;
			if (G.kind == GraphKind::DG) arc++;
		}
		if (p) {
			if (p->adjvex > i) p->adjvex--;
			pre = p;
			p = p->nextarc;
		}
		while (p) {
			if (p->adjvex == i) {
				pre->nextarc = p->nextarc;
				free(p);//p=NULL;可修复warning
				p = pre->nextarc;
				if (G.kind == GraphKind::DG) arc++;
			}
			else {
				if (p->adjvex > i)
					p->adjvex--;
				pre = p; p = p->nextarc;
			}
		}
	}
	G.arcnum -= arc;
	return OK;
}//DeleteVex

Status InsertArc(ALGraph& G, char v, char w) {
	//插入弧<v,w>，如果是无向图则对称插入<w,v>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcNode* p = G.vertices[i].firstarc;
	while (p) {
		if (p->adjvex == j) return ERROR;//弧已存在
		p = p->nextarc;
	}
	p = (ArcNode*)malloc(sizeof(ArcNode));
	if (!p) return ERROR;
	p->adjvex = j;
	p->nextarc = G.vertices[i].firstarc;//头插
	G.vertices[i].firstarc = p;
	G.arcnum++;
	if (G.kind == GraphKind::UDG) {//无向图对称插入
		ArcNode* q = (ArcNode*)malloc(sizeof(ArcNode));
		if (!q) return ERROR;
		q->adjvex = i;
		q->nextarc = G.vertices[j].firstarc;//头插
		G.vertices[j].firstarc = q;
	}
	return OK;
}//InsertArc

Status DeleteArc(ALGraph& G, char v, char w) {
	//删除弧<v,w>，如果是无向图则对称删除<w,v>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcNode* p = G.vertices[i].firstarc, * pre = NULL;
	while (p && p->adjvex != j) {
		pre = p; p = p->nextarc;
	}
	if (!p) return ERROR;//弧不存在
	if (p == G.vertices[i].firstarc) //有可能第一个结点就是弧<v,w>，此时不能用pre来删除
		G.vertices[i].firstarc = p->nextarc;
	else
		pre->nextarc = p->nextarc;
	free(p);
	G.arcnum--;
	if (G.kind == GraphKind::UDG) {
		p = G.vertices[j].firstarc; pre = NULL;
		while (p && p->adjvex != i) {
			pre = p; p = p->nextarc;
		}
		if (!p) return ERROR;//无向图缺失结点报错
		if (p == G.vertices[j].firstarc) //有可能第一个结点就是弧<w,v>，此时不能用pre来删除
			G.vertices[j].firstarc = p->nextarc;
		else
			pre->nextarc = p->nextarc;
		free(p);
	}
	return OK;
}//DeleteArc

/*有向图的十字链表存储下的基本函数*/

Status CreateGraph(OLGraph& G) {
	//创建十字链表有向图G
	int IncInfo;
	printf("依次输入顶点数，弧数，弧有无额外信息0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfo为0时，弧不含其他信息
	getchar();
	for (int i = 0; i < G.vexnum; ++i) {
		scanf_s("%c", &G.xlist[i].data, 1);//构造顶点数组
		G.xlist[i].firstin = G.xlist[i].firstout = NULL;
	}
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//输入该边的两顶点，有序
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		ArcBox* p = (ArcBox*)malloc(sizeof(ArcBox));
		if (!p) return ERROR;
		p->headvex = j; p->tailvex = i;
		p->tlink = G.xlist[i].firstout;
		G.xlist[i].firstout = p;
		p->hlink = G.xlist[j].firstin;
		G.xlist[j].firstin = p;
		p->info = NULL;
		if (IncInfo);//分配空间并Input(*p->Info);
	}
	return OK;
}//CreateGraph

int LocateVex(OLGraph G, char v) {
	//定位顶点v在十字链表图G中的位置
	for (int i = 0; i < G.vexnum; ++i)
		if (G.xlist[i].data == v)
			return i;
	return -1;
}//LocateVex

Status DestroyGraph(OLGraph& G) {
	//销毁十字链表图G
	ArcBox* p, * pre;
	for (int i = 0; i < G.vexnum; ++i) {
		p = G.xlist[i].firstout; pre = NULL;
		while (p) {
			pre = p; p = p->tlink; free(pre);
		}
		G.xlist[i].firstout = NULL;
	}
	return OK;
}//DestroyGraph

int FirstOutVex(OLGraph G, char v) {
	//返回顶点v的第一个出弧顶点，若无返回空
	int i = LocateVex(G, v);
	if (!G.xlist[i].firstout) return -1;
	else return G.xlist[i].firstout->headvex;
}//FirstOutVex

int FirstInVex(OLGraph G, char v) {
	//返回顶点v的第一个入弧顶点，若无返回空
	int i = LocateVex(G, v);
	if (!G.xlist[i].firstin) return -1;
	else return G.xlist[i].firstin->tailvex;
}//FirstInVex

int NextOutVex(OLGraph G, char v, char w) {
	//w，v为十字链表有向图G上的顶点，w在v出弧链上，返回该链w下一个顶点，若无返回空
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcBox* p = G.xlist[i].firstout;
	while (p && p->headvex != j) p = p->tlink;
	if (!p) return -1;
	if (!p->tlink) return -1;
	else return p->tlink->headvex;
}//NextOutVex

int NextInVex(OLGraph G, char v, char w) {
	//w，v为十字链表有向图G上的顶点，w在v入弧链上，返回该链w下一个顶点，若无返回空
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcBox* p = G.xlist[i].firstin;
	while (p && p->tailvex != j) p = p->hlink;
	if (!p) return -1;
	if (!p->hlink) return -1;
	else return p->hlink->tailvex;
}//NextInVex

Status InsertVex(OLGraph& G, char v) {
	//在有向图G中添加顶点v
	if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;//顶点已满
	G.xlist[G.vexnum].data = v;
	G.xlist[G.vexnum].firstin = G.xlist[G.vexnum].firstout = NULL;
	G.vexnum++;
	return OK;
}//InsertVex

Status DeleteVex(OLGraph& G, char v) {
	//删除有向图G中的顶点v以及依附于其的弧
	int arc = 0;//记录删去的弧数e
	int i = LocateVex(G, v);
	ArcBox* p, * pre;
	while (G.xlist[i].firstout) {//去除出弧
		int j = G.xlist[i].firstout->headvex;
		p = G.xlist[j].firstin; pre = NULL;
		if (p->tailvex == i)
			G.xlist[j].firstin = p->hlink;
		else {
			while (p->tailvex != i) {
				pre = p; p = p->hlink;
			}
			pre->hlink = p->hlink;

		}
		G.xlist[i].firstout = p->tlink;
		free(p);
		arc++;
	}
	while (G.xlist[i].firstin) {//去除入弧
		int j = G.xlist[i].firstin->tailvex;
		p = G.xlist[j].firstout; pre = NULL;
		if (p->headvex == i)
			G.xlist[j].firstout = p->tlink;
		else {
			while (p->headvex != i) {
				pre = p; p = p->tlink;
			}
			pre->tlink = p->tlink;

		}
		G.xlist[i].firstin = p->hlink;
		free(p);
		arc++;
	}
	G.arcnum -= arc;
	for (int j = i; j < G.vexnum - 1; ++j) {
		G.xlist[j].data = G.xlist[j + 1].data;
		G.xlist[j].firstin = G.xlist[j + 1].firstin;
		G.xlist[j].firstout = G.xlist[j + 1].firstout;
	}
	G.xlist[G.vexnum - 1].firstin = G.xlist[G.vexnum - 1].firstout = NULL;
	G.vexnum--;
	for (int j = 0; j < G.vexnum; ++j) {
		p = G.xlist[j].firstout;
		while (p) {
			if (p->headvex > i)
				p->headvex--;
			if (p->tailvex > i)
				p->tailvex--;
			p = p->tlink;
		}
	}
	return OK;
}//DeleteVex

Status InsertArc(OLGraph& G, char v, char w) {
	//向十字链表有向图G中插入弧<v,w>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcBox* p = G.xlist[i].firstout;
	while (p) {
		if (p->headvex == j) return ERROR;//已有该弧
		p = p->tlink;
	}
	p = (ArcBox*)malloc(sizeof(ArcBox));
	if (!p) return ERROR;
	p->headvex = j; p->tailvex = i;
	p->info = NULL;
	p->tlink = G.xlist[i].firstout;
	G.xlist[i].firstout = p;
	p->hlink = G.xlist[j].firstin;
	G.xlist[j].firstin = p;
	G.arcnum++;
	return OK;
} //InsertArc

Status DeleteArc(OLGraph& G, char v, char w) {
	//删除有向图G中的弧<v,w>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcBox* p, * pre;
	p = G.xlist[i].firstout; pre = NULL;
	if (p && p->headvex == j)
		G.xlist[i].firstout = p->tlink;
	else {
		while (p && p->headvex != j) {
			pre = p; p = p->tlink;
		}
		if (!p) return ERROR;//弧不存在
		pre->tlink = p->tlink;
	}
	p = G.xlist[j].firstin; pre = NULL;
	if (p && p->tailvex == i) {
		G.xlist[j].firstin = p->hlink;
	}
	else {
		while (p && p->tailvex != i) {
			pre = p; p = p->hlink;
		}
		if (!p) return ERROR;//弧不存在
		pre->hlink = p->hlink;
	}
	free(p);
	G.arcnum--;
	return OK;
}//DeleteArc

/*无向图的邻接多重表存储下的基本函数*/

Status CreateGraph(AMLGraph& G) {
	//多重邻接表法创建有向图G
	int IncInfo;
	printf("依次输入顶点数，弧数，弧有无额外信息0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfo为0时，弧不含其他信息
	getchar();
	for (int i = 0; i < G.vexnum; ++i) {
		scanf_s("%c", &G.adjmulist[i].data, 1);//构造顶点数组
		G.adjmulist[i].firstedge = NULL;
	}
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//输入该边的两顶点
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		EBox* p = (EBox*)malloc(sizeof(EBox));
		if (!p) return ERROR;
		p->ivex = i; p->jvex = j;
		p->info = NULL; p->mark = VisitIf::unvisited;
		p->ilink = G.adjmulist[i].firstedge;
		G.adjmulist[i].firstedge = p;
		p->jlink = G.adjmulist[j].firstedge;
		G.adjmulist[j].firstedge = p;
		if (IncInfo);//分配空间并Input(*p->Info);
	}
	return OK;
}//CreateGraph

int LocateVex(AMLGraph G, char v) {
	//返回顶点v邻接多重表无向图G中的位置
	for (int i = 0; i < G.vexnum; ++i)
		if (G.adjmulist[i].data == v)
			return i;
	return -1;
}//LocateVex

Status DestroyGraph(AMLGraph& G) {
	//销毁无向图G
	EBox* p, * pre;
	for (int i = 0; i < G.vexnum; ++i) {
		p = G.adjmulist[i].firstedge; pre = NULL;
		while (p) {
			pre = p;
			p = p->ivex == i ? p->ilink : p->jlink;
			if (pre->mark == VisitIf::unvisited)
				pre->mark = VisitIf::visited;
			else
				free(pre);
		}
	}
	return OK;
}//DestroyGraph

int FirstAdjVex(AMLGraph G, char v) {
	//返回无向图G中顶点v的第一个邻接顶点，若无返回空
	int i = LocateVex(G, v);
	if (!G.adjmulist[i].firstedge) return -1;
	return G.adjmulist[i].firstedge->ivex == i ? G.adjmulist[i].firstedge->jvex : G.adjmulist[i].firstedge->ivex;
}//FirstAdjVex

int NextAdjVex(AMLGraph G, char v, char w) {
	//无向图G中，返回在v的邻接顶点中，w的下一个顶点，若无返回空；
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	EBox* p = G.adjmulist[i].firstedge;
	while (p && p->ivex != j && p->jvex != j)
		p = p->ivex == i ? p->ilink : p->jlink;
	if (!p) return -1;//(v,w)不存在
	if (p->ivex == i)
		if (!p->ilink) return -1;
		else return p->ilink->ivex == i ? p->ilink->jvex : p->ilink->ivex;
	else
		if (!p->jlink) return -1;
		else
			return p->jlink->ivex == i ? p->jlink->jvex : p->jlink->ivex;
}//NextAdjVex

Status InsertVex(AMLGraph& G, char v) {
	//无向图G中插入新顶点v
	if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;
	G.adjmulist[G.vexnum].data = v;
	G.adjmulist[G.vexnum].firstedge = NULL;
	G.vexnum++;
	return OK;
}//InsertVex

Status DeleteVex(AMLGraph& G, char v) {
	//无向图G中删除顶点v和依附于其的边
	int arc = 0;//记录删去的弧数e
	int i = LocateVex(G, v);
	EBox* p, * pre;
	while (G.adjmulist[i].firstedge) {
		int j = G.adjmulist[i].firstedge->ivex == i ? G.adjmulist[i].firstedge->jvex : G.adjmulist[i].firstedge->ivex;
		p = G.adjmulist[j].firstedge; pre = NULL;
		if (p == G.adjmulist[i].firstedge)
			G.adjmulist[j].firstedge = p->ivex == j ? p->ilink : p->jlink;
		else {
			while (p != G.adjmulist[i].firstedge) {
				pre = p;
				p = p->ivex == j ? p->ilink : p->jlink;
			}
			if (pre->ivex == j)
				pre->ilink = p->ivex == j ? p->ilink : p->jlink;
			else
				pre->jlink = p->ivex == j ? p->ilink : p->jlink;
		}
		G.adjmulist[i].firstedge = p->ivex == i ? p->ilink : p->jlink;
		free(p);
		arc++;
	}
	G.arcnum -= arc;
	for (int j = 0; j < G.vexnum; ++j) {
		//注意！必须先将结点中的顶点值（>v）减一，才能进行顶点缩进，否则如果先缩进，在此循环中p向下一结点移动不能按预期进行
		p = G.adjmulist[j].firstedge;
		while (p) {
			int sign = 0;
			if (p->mark == VisitIf::unvisited) {
				p->mark = VisitIf::visited;
				p = p->ivex == j ? p->ilink : p->jlink;
			}
			else {
				p->mark = VisitIf::unvisited;
				if (p->ivex > i) {
					p->ivex--; sign = 1;//sign记录ivex有没有减一
				}
				if (p->jvex > i)
					p->jvex--;
				if (sign == 1)
					p = p->ivex + 1 == j ? p->ilink : p->jlink;
				else p = p->ivex == j ? p->ilink : p->jlink;
			}

		}
	}
	for (int j = i; j < G.vexnum - 1; ++j) {
		G.adjmulist[j].data = G.adjmulist[j + 1].data;//为什么对于十字链表中同样的写法，就没有报错
		G.adjmulist[j].firstedge = G.adjmulist[j + 1].firstedge;
	}
	G.adjmulist[G.vexnum - 1].firstedge = NULL;//此处及上面的缓冲区溢出报错，是在我将 顶点前缩循环 从 顶点值减一循环 之前放在这里后才出现的
	G.vexnum--;
	return OK;
}//DeleteVex

Status InsertEdge(AMLGraph& G, char v, char w) {
	//无向图G中插入边(v,w)
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	EBox* p = G.adjmulist[i].firstedge;
	while (p) {
		if (p->ivex == j || p->jvex == j) return ERROR;//边已存在
		p = p->ivex == i ? p->ilink : p->jlink;
	}
	p = (EBox*)malloc(sizeof(EBox));
	if (!p) return ERROR;
	p->ivex = i; p->jvex = j;
	p->mark = VisitIf::unvisited;
	p->info = NULL;
	p->ilink = G.adjmulist[i].firstedge;
	G.adjmulist[i].firstedge = p;
	p->jlink = G.adjmulist[j].firstedge;
	G.adjmulist[j].firstedge = p;
	G.arcnum++;
	return OK;
}//InsertEdge

Status DeleteEdge(AMLGraph& G, char v, char w) {
	//无向图G中删除边(v,w)
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	EBox* p = G.adjmulist[i].firstedge, * pre = NULL;
	if (p->ivex == j || p->jvex == j)
		G.adjmulist[i].firstedge = p->ivex == i ? p->ilink : p->jlink;
	else {
		while (p && p->ivex != j && p->jvex != j) {
			pre = p;
			p = p->ivex == i ? p->ilink : p->jlink;
		}
		if (!p) return ERROR;//边不存在
		if (pre->ivex == i)
			pre->ilink = p->ivex == i ? p->ilink : p->jlink;
		else
			pre->jlink = p->ivex == i ? p->ilink : p->jlink;
	}
	p = G.adjmulist[j].firstedge; pre = NULL;
	if (p->ivex == i || p->jvex == i)
		G.adjmulist[j].firstedge = p->ivex == j ? p->ilink : p->jlink;
	else {
		while (p && p->ivex != i && p->jvex != i) {
			pre = p;
			p = p->ivex == j ? p->ilink : p->jlink;
		}
		if (!p) return ERROR;//边不存在
		if (pre->ivex == j)
			pre->ilink = p->ivex == j ? p->ilink : p->jlink;
		else
			pre->jlink = p->ivex == j ? p->ilink : p->jlink;
	}
	free(p);
	G.arcnum--;
	return OK;
}//DeleteEdge

/*图的两种遍历*/

Status DFSTraverse(MGraph G, Status(*visit)(char a)) {
	//对图G作深度优先遍历，存储结构为邻接矩阵
	VisitFunc = visit;
	for (int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;//初始化标志数组
	for (int i = 0; i < G.vexnum; ++i)
		if (!visited[i])
			DFS(G, i);
	return OK;
}//DFSTraverse

Status DFS(MGraph G, int i) {
	//从位置为i的顶点出发深度优先遍历
	visited[i] = TRUE;
	if (!(*VisitFunc)(G.vexs[i])) return ERROR;
	for (int j = FirstAdjVex(G, G.vexs[i]); j >= 0; j = NextAdjVex(G, G.vexs[i], G.vexs[j]))
		if (!visited[j]) DFS(G, j);
	return OK;
}//DFS

Status DFSTraverse(ALGraph G, Status(*visit)(char a)) {
	//对图G作深度优先遍历，存储结构为邻接矩阵
	VisitFunc = visit;
	for (int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;//初始化标志数组
	for (int i = 0; i < G.vexnum; ++i)
		if (!visited[i])
			DFS(G, i);
	return OK;
}//DFSTraverse

Status DFS(ALGraph G, int i) {
	//从位置为i的顶点出发深度优先遍历
	visited[i] = TRUE;
	if (!(*VisitFunc)(G.vertices[i].data)) return ERROR;
	for (int j = FirstAdjVex(G, G.vertices[i].data); j >= 0; j = NextAdjVex(G, G.vertices[i].data, G.vertices[j].data))
		if (!visited[j]) DFS(G, j);
	return OK;
}//DFS

Status DFSTraverse(OLGraph G, Status(*visit)(char a)) {
	//对图G作深度优先遍历，存储结构为邻接矩阵
	VisitFunc = visit;
	for (int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;//初始化标志数组
	for (int i = 0; i < G.vexnum; ++i)
		if (!visited[i])
			DFS(G, i);
	return OK;
}//DFSTraverse

Status DFS(OLGraph G, int i) {
	//从位置为i的顶点出发深度优先遍历
	visited[i] = TRUE;
	if (!(*VisitFunc)(G.xlist[i].data)) return ERROR;
	for (int j = FirstOutVex(G, G.xlist[i].data); j >= 0; j = NextOutVex(G, G.xlist[i].data, G.xlist[j].data))
		if (!visited[j]) DFS(G, j);
	return OK;
}//DFS

Status DFSTraverse(AMLGraph G, Status(*visit)(char a)) {
	//对图G作深度优先遍历，存储结构为邻接矩阵
	VisitFunc = visit;
	for (int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;//初始化标志数组
	for (int i = 0; i < G.vexnum; ++i)
		if (!visited[i])
			DFS(G, i);
	return OK;
}//DFSTraverse

Status DFS(AMLGraph G, int i) {
	//从位置为i的顶点出发深度优先遍历
	visited[i] = TRUE;
	if (!(*VisitFunc)(G.adjmulist[i].data)) return ERROR;
	for (int j = FirstAdjVex(G, G.adjmulist[i].data); j >= 0; j = NextAdjVex(G, G.adjmulist[i].data, G.adjmulist[j].data))
		if (!visited[j]) DFS(G, j);
	return OK;
}//DFS