# include "Graph.h"

/*ͼ���ڽӾ���洢�µĻ�����������*/

Status CreateGraph(MGraph& G) {
	//�ڽӾ��󷨴���ͼG
	printf("����ͼ�����ͣ�����ͼ0��������1������ͼ2��������3:\n");
	scanf_s("%d", &G.kind);//0-3�ֱ����DG,DN,UDG,UDN
	switch (G.kind) {
	case GraphKind::DG: return CreateDG(G);
	case GraphKind::DN: return CreateDN(G);
	case GraphKind::UDG: return CreateUDG(G);
	case GraphKind::UDN: return CreateUDN(G);
	default: return ERROR;
	}
}//CreateGraph

int LocateVex(MGraph G, char v) {
	//ȷ������v��ͼ���������е��±�
	for (int i = 0; i < G.vexnum; ++i)
		if (G.vexs[i] == v) return i;
	return -1;
}//LocateVex

Status CreateDG(MGraph& G) {
	//��������ͼG
	int IncInfo;
	printf("�������붥�����������������޶�����Ϣ0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfoΪ0ʱ��������������Ϣ
	getchar();//������з�
	for (int i = 0; i < G.vexnum; ++i) scanf_s("%c", &G.vexs[i]);//���춥������
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			G.arcs[i][j] = { 0,NULL };//�ڽӾ����ʼ��
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//����ñߵ������㣬����
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
		if (IncInfo);//Input(*G.arcs[i][j].info);
	}
	return OK;
}//CreateDG

Status CreateUDG(MGraph& G) {
	//��������ͼG
	int IncInfo;
	printf("�������붥�����������������޶�����Ϣ0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfoΪ0ʱ��������������Ϣ
	getchar();//������з�
	for (int i = 0; i < G.vexnum; ++i) scanf_s("%c", &G.vexs[i], 1);//���춥������
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			G.arcs[i][j] = { 0,NULL };//�ڽӾ����ʼ��
	for (int i = G.vexnum; i < MAX_VERTEX_NUM; ++i) G.vexs[i] = 0;
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//����ñߵ�������
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
		if (IncInfo);//Input(*G.arcs[i][j].info);
		G.arcs[j][i] = G.arcs[i][j];
	}
	return OK;
}//CreateUDG

Status CreateDN(MGraph& G) {
	//����������G
	int IncInfo;
	printf("�������붥�����������������޶�����Ϣ0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfoΪ0ʱ��������������Ϣ
	getchar();//������з�
	for (int i = 0; i < G.vexnum; ++i) scanf_s("%c", &G.vexs[i]);//���춥������
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			G.arcs[i][j] = { INFINITY,NULL };//�ڽӾ����ʼ��
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		int weight;
		scanf_s(" %c %c %d", &v1, 1, &v2, 1, &weight);//����ñߵ������㼰Ȩ��
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = weight;
		if (IncInfo);//Input(*G.arcs[i][j].info);
	}
	return OK;
}//CreateDN

Status CreateUDN(MGraph& G) {
	//����������G
	int IncInfo;
	printf("�������붥�����������������޶�����Ϣ0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfoΪ0ʱ��������������Ϣ
	getchar();//������з�
	for (int i = 0; i < G.vexnum; ++i) scanf_s("%c", &G.vexs[i]);//���춥������
	for (int i = 0; i < MAX_VERTEX_NUM; ++i)
		for (int j = 0; j < MAX_VERTEX_NUM; ++j)
			G.arcs[i][j] = { INFINITY,NULL };//�ڽӾ����ʼ��
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		int weight;
		scanf_s(" %c %c %d", &v1, 1, &v2, 1, &weight);//����ñߵ������㼰Ȩ��
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		G.arcs[i][j].adj = weight;
		if (IncInfo);//Input(*G.arcs[i][j].info);
		G.arcs[j][i] = G.arcs[i][j];
	}
	return OK;
}//CreateUDN

Status DestroyGraph(MGraph& G) {
	//����ͼG
	//G�е�Ԫ�ذ���һά�Ͷ�ά���鶼��ջ�ϵ��ڴ���Զ��ͷ�
	return OK;
}//DestroyGraph

int FirstAdjVex(MGraph G, char v) {
	//��������ͼG�ж���v�ĵ�һ���ڽӶ��㣬�����򷵻ؿ�
	//����ͼΪ�������ڽӶ��㣬��ͬ
	//ע�ⷵ���ڽӶ��㷵�صĶ���λ�ã����ƺ�����ͬ
	int i = LocateVex(G, v);
	for (int j = 0; j < G.vexnum; ++j)
		if (G.arcs[i][j].adj == 1)
			return j;
	return -1;
}//FirstAdjvex

int NextAdjVex(MGraph G, char v, char w) {
	//����ͼG��wΪv���ڽӶ��㣬����v����һ���ڽӶ��㣬��wΪ���һ�������ؿ�
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	for (int k = j + 1; k < G.vexnum; ++k)
		if (G.arcs[i][k].adj == 1)
			return k;
	return -1;
}//NextAdjVex

Status InsertVex(MGraph& G, char v) {
	//��ͼ����G�������½��v
	if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;//�ڴ�����
	G.vexs[G.vexnum] = v;
	G.vexnum++;
	return OK;
}//InsertVex

Status DeleteVex(MGraph& G, char v) {
	//ɾ��ͼ����G�еĶ���v���Լ���صĻ�
	int i = LocateVex(G, v);
	for (int j = i; j < G.vexnum - 1; ++j) G.vexs[j] = G.vexs[j + 1];
	int arc = 0;//��v�й�ϵ�Ļ���
	for (int j = 0; j < G.vexnum; ++j) {
		if (G.kind == GraphKind::DG)//����ͼ
			if (G.arcs[i][j].adj == 1) arc++;
		if (G.kind == GraphKind::DN)//������
			if (G.arcs[i][j].adj != INFINITY) arc++;
		if (G.kind == GraphKind::UDG)//����ͼ
			if (G.arcs[i][j].adj == 1) arc++;
		if (G.kind == GraphKind::UDN)//������
			if (G.arcs[i][j].adj != INFINITY) arc++;
	}
	if (G.kind == GraphKind::DG || G.kind == GraphKind::DN) {//����Ҳ��Ҫ������
		for (int j = 0; j < G.vexnum; ++j) {
			if (G.kind == GraphKind::DG)//����ͼ
				if (G.arcs[j][i].adj == 1) arc++;
			if (G.kind == GraphKind::DN)//������
				if (G.arcs[j][i].adj != INFINITY) arc++;
		}
	}
	//������ɾ����ά�����i�к�i��
	for (int j = 1; j < G.vexnum; ++j) {//ɾ��i��
		for (int k = i; k < G.vexnum - 1; ++k)
			G.arcs[k][j] = G.arcs[k + 1][j];
	}
	for (int j = 1; j < G.vexnum; ++j) {//ɾ��i��
		for (int k = i; k < G.vexnum - 1; ++k)
			G.arcs[j][k] = G.arcs[j][k + 1];
	}
	G.arcnum -= arc;
	G.vexnum--;
	return OK;
}//DeleteVex

Status InsertArc(MGraph& G, char v, char w) {
	//��ͼG������<v,w>����ͼ����ͬʱ���ӶԳƵ�<w,v>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	if (G.arcs[i][j].adj == 0) G.arcnum++;//��ʱ�߲�����
	G.arcs[i][j].adj = 1;
	if (G.kind == GraphKind::UDG)
		G.arcs[j][i].adj = 1;
	return OK;
}//InsertArc

Status InsertArc(MGraph& G, char v, char w, int weight) {
	//����G������<v,w>��Ȩ��Ϊweight����ͼ����ͬʱ���ӶԳƵ�<w,v>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	if (G.arcs[i][j].adj == INFINITY) G.arcnum++;//��ʱ�߲�����
	G.arcs[i][j].adj = weight;
	if (G.kind == GraphKind::UDN)
		G.arcs[j][i].adj = weight;
	return OK;
}//InsertArc

Status DeleteArc(MGraph& G, char v, char w) {
	//ɾ��ͼ����G�еĻ�<v,w>�����ͼ����ͬʱɾ����<w,v>
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

/*ͼ���ڽӱ�洢�µĻ�����������*/

Status CreateGraph(ALGraph& G) {
	//�ڽӱ�����ͼG
	printf("����ͼ�����ͣ�����ͼ0������ͼ2:\n");
	scanf_s("%d", &G.kind);//0��2�ֱ����DG,UDG
	int IncInfo;
	printf("�������붥�����������������޶�����Ϣ0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfoΪ0ʱ��������������Ϣ
	getchar();
	for (int i = 0; i < G.vexnum; ++i) {
		scanf_s("%c", &G.vertices[i].data);//���춥������
		G.vertices[i].firstarc = NULL;
	}
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//����ñߵ������㣬����
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		if (!p) return ERROR;
		p->adjvex = j;
		p->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p;//ͷ��
		if (IncInfo);//Input(*p->Info);
		if (G.kind == GraphKind::UDG) {//����ͼʱ�ԳƲ���
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
	//���Ҷ���v��ͼG�е�λ��
	for (int i = 0; i < G.vexnum; ++i)
		if (G.vertices[i].data == v)
			return i;
	return -1;
}//LocateVex

Status DestroyGraph(ALGraph& G) {
	//�����ڽӱ�ͼG
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
	//����ͼG��v�ĵ�һ���ڽӶ��㣬��������ͼ���ص����ڽ���v��
	//�����ڽӵ�v�Ķ��㣬��Ҫ����ȫ��Ѱ��
	int i = LocateVex(G, v);
	if (!G.vertices[i].firstarc) return -1;//���ڽ�
	return G.vertices[i].firstarc->adjvex;
}//FirstAdjVex

int NextAdjVex(ALGraph G, char v, char w) {
	//����ͼG��v���ڽӶ����е�w����һ�����㣬��������ͼ���ص����ڽ���v��
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
	//��ͼG����Ӷ���v
	if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;//��������
	G.vertices[G.vexnum].data = v;
	G.vertices[G.vexnum].firstarc = NULL;
	G.vexnum++;
	return OK;
}//InsertVex

Status DeleteVex(ALGraph& G, char v) {
	//ɾ��ͼG�еĶ���v�Լ���������Ļ�
	int arc = 0;//��¼ɾȥ�Ļ���e
	int i = LocateVex(G, v);
	ArcNode* p, * pre;
	p = G.vertices[i].firstarc;
	pre = NULL;
	while (p) {
		pre = p; p = p->nextarc; free(pre); arc++;
	}
	for (int j = i; j < G.vexnum - 1; ++j) {//��������ǰ��
		G.vertices[j].data = G.vertices[j + 1].data;
		G.vertices[j].firstarc = G.vertices[j + 1].firstarc;
	}
	G.vertices[G.vexnum - 1].firstarc = NULL;
	G.vexnum--;
	for (int j = 0; j < G.vexnum; ++j) {//�������н�㣬ɾ���ڽӵ�v�Ļ���㣬�ҽ�����ǰ�������λ��ֵ����1
		p = G.vertices[j].firstarc; pre = NULL;
		while (p && p->adjvex == i) {//ͷ��������뻡��㲻һ������������pre��ɾ��
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
				free(p);//p=NULL;���޸�warning
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
	//���뻡<v,w>�����������ͼ��ԳƲ���<w,v>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcNode* p = G.vertices[i].firstarc;
	while (p) {
		if (p->adjvex == j) return ERROR;//���Ѵ���
		p = p->nextarc;
	}
	p = (ArcNode*)malloc(sizeof(ArcNode));
	if (!p) return ERROR;
	p->adjvex = j;
	p->nextarc = G.vertices[i].firstarc;//ͷ��
	G.vertices[i].firstarc = p;
	G.arcnum++;
	if (G.kind == GraphKind::UDG) {//����ͼ�ԳƲ���
		ArcNode* q = (ArcNode*)malloc(sizeof(ArcNode));
		if (!q) return ERROR;
		q->adjvex = i;
		q->nextarc = G.vertices[j].firstarc;//ͷ��
		G.vertices[j].firstarc = q;
	}
	return OK;
}//InsertArc

Status DeleteArc(ALGraph& G, char v, char w) {
	//ɾ����<v,w>�����������ͼ��Գ�ɾ��<w,v>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcNode* p = G.vertices[i].firstarc, * pre = NULL;
	while (p && p->adjvex != j) {
		pre = p; p = p->nextarc;
	}
	if (!p) return ERROR;//��������
	if (p == G.vertices[i].firstarc) //�п��ܵ�һ�������ǻ�<v,w>����ʱ������pre��ɾ��
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
		if (!p) return ERROR;//����ͼȱʧ��㱨��
		if (p == G.vertices[j].firstarc) //�п��ܵ�һ�������ǻ�<w,v>����ʱ������pre��ɾ��
			G.vertices[j].firstarc = p->nextarc;
		else
			pre->nextarc = p->nextarc;
		free(p);
	}
	return OK;
}//DeleteArc

/*����ͼ��ʮ������洢�µĻ�������*/

Status CreateGraph(OLGraph& G) {
	//����ʮ����������ͼG
	int IncInfo;
	printf("�������붥�����������������޶�����Ϣ0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfoΪ0ʱ��������������Ϣ
	getchar();
	for (int i = 0; i < G.vexnum; ++i) {
		scanf_s("%c", &G.xlist[i].data, 1);//���춥������
		G.xlist[i].firstin = G.xlist[i].firstout = NULL;
	}
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//����ñߵ������㣬����
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
		if (IncInfo);//����ռ䲢Input(*p->Info);
	}
	return OK;
}//CreateGraph

int LocateVex(OLGraph G, char v) {
	//��λ����v��ʮ������ͼG�е�λ��
	for (int i = 0; i < G.vexnum; ++i)
		if (G.xlist[i].data == v)
			return i;
	return -1;
}//LocateVex

Status DestroyGraph(OLGraph& G) {
	//����ʮ������ͼG
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
	//���ض���v�ĵ�һ���������㣬���޷��ؿ�
	int i = LocateVex(G, v);
	if (!G.xlist[i].firstout) return -1;
	else return G.xlist[i].firstout->headvex;
}//FirstOutVex

int FirstInVex(OLGraph G, char v) {
	//���ض���v�ĵ�һ���뻡���㣬���޷��ؿ�
	int i = LocateVex(G, v);
	if (!G.xlist[i].firstin) return -1;
	else return G.xlist[i].firstin->tailvex;
}//FirstInVex

int NextOutVex(OLGraph G, char v, char w) {
	//w��vΪʮ����������ͼG�ϵĶ��㣬w��v�������ϣ����ظ���w��һ�����㣬���޷��ؿ�
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcBox* p = G.xlist[i].firstout;
	while (p && p->headvex != j) p = p->tlink;
	if (!p) return -1;
	if (!p->tlink) return -1;
	else return p->tlink->headvex;
}//NextOutVex

int NextInVex(OLGraph G, char v, char w) {
	//w��vΪʮ����������ͼG�ϵĶ��㣬w��v�뻡���ϣ����ظ���w��һ�����㣬���޷��ؿ�
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcBox* p = G.xlist[i].firstin;
	while (p && p->tailvex != j) p = p->hlink;
	if (!p) return -1;
	if (!p->hlink) return -1;
	else return p->hlink->tailvex;
}//NextInVex

Status InsertVex(OLGraph& G, char v) {
	//������ͼG����Ӷ���v
	if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;//��������
	G.xlist[G.vexnum].data = v;
	G.xlist[G.vexnum].firstin = G.xlist[G.vexnum].firstout = NULL;
	G.vexnum++;
	return OK;
}//InsertVex

Status DeleteVex(OLGraph& G, char v) {
	//ɾ������ͼG�еĶ���v�Լ���������Ļ�
	int arc = 0;//��¼ɾȥ�Ļ���e
	int i = LocateVex(G, v);
	ArcBox* p, * pre;
	while (G.xlist[i].firstout) {//ȥ������
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
	while (G.xlist[i].firstin) {//ȥ���뻡
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
	//��ʮ����������ͼG�в��뻡<v,w>
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	ArcBox* p = G.xlist[i].firstout;
	while (p) {
		if (p->headvex == j) return ERROR;//���иû�
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
	//ɾ������ͼG�еĻ�<v,w>
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
		if (!p) return ERROR;//��������
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
		if (!p) return ERROR;//��������
		pre->hlink = p->hlink;
	}
	free(p);
	G.arcnum--;
	return OK;
}//DeleteArc

/*����ͼ���ڽӶ��ر�洢�µĻ�������*/

Status CreateGraph(AMLGraph& G) {
	//�����ڽӱ���������ͼG
	int IncInfo;
	printf("�������붥�����������������޶�����Ϣ0/1:\n");
	scanf_s("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);//IncInfoΪ0ʱ��������������Ϣ
	getchar();
	for (int i = 0; i < G.vexnum; ++i) {
		scanf_s("%c", &G.adjmulist[i].data, 1);//���춥������
		G.adjmulist[i].firstedge = NULL;
	}
	for (int k = 0; k < G.arcnum; ++k) {
		char v1, v2;
		scanf_s(" %c %c", &v1, 1, &v2, 1);//����ñߵ�������
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
		if (IncInfo);//����ռ䲢Input(*p->Info);
	}
	return OK;
}//CreateGraph

int LocateVex(AMLGraph G, char v) {
	//���ض���v�ڽӶ��ر�����ͼG�е�λ��
	for (int i = 0; i < G.vexnum; ++i)
		if (G.adjmulist[i].data == v)
			return i;
	return -1;
}//LocateVex

Status DestroyGraph(AMLGraph& G) {
	//��������ͼG
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
	//��������ͼG�ж���v�ĵ�һ���ڽӶ��㣬���޷��ؿ�
	int i = LocateVex(G, v);
	if (!G.adjmulist[i].firstedge) return -1;
	return G.adjmulist[i].firstedge->ivex == i ? G.adjmulist[i].firstedge->jvex : G.adjmulist[i].firstedge->ivex;
}//FirstAdjVex

int NextAdjVex(AMLGraph G, char v, char w) {
	//����ͼG�У�������v���ڽӶ����У�w����һ�����㣬���޷��ؿգ�
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	EBox* p = G.adjmulist[i].firstedge;
	while (p && p->ivex != j && p->jvex != j)
		p = p->ivex == i ? p->ilink : p->jlink;
	if (!p) return -1;//(v,w)������
	if (p->ivex == i)
		if (!p->ilink) return -1;
		else return p->ilink->ivex == i ? p->ilink->jvex : p->ilink->ivex;
	else
		if (!p->jlink) return -1;
		else
			return p->jlink->ivex == i ? p->jlink->jvex : p->jlink->ivex;
}//NextAdjVex

Status InsertVex(AMLGraph& G, char v) {
	//����ͼG�в����¶���v
	if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;
	G.adjmulist[G.vexnum].data = v;
	G.adjmulist[G.vexnum].firstedge = NULL;
	G.vexnum++;
	return OK;
}//InsertVex

Status DeleteVex(AMLGraph& G, char v) {
	//����ͼG��ɾ������v����������ı�
	int arc = 0;//��¼ɾȥ�Ļ���e
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
		//ע�⣡�����Ƚ�����еĶ���ֵ��>v����һ�����ܽ��ж�������������������������ڴ�ѭ����p����һ����ƶ����ܰ�Ԥ�ڽ���
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
					p->ivex--; sign = 1;//sign��¼ivex��û�м�һ
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
		G.adjmulist[j].data = G.adjmulist[j + 1].data;//Ϊʲô����ʮ��������ͬ����д������û�б���
		G.adjmulist[j].firstedge = G.adjmulist[j + 1].firstedge;
	}
	G.adjmulist[G.vexnum - 1].firstedge = NULL;//�˴�������Ļ�����������������ҽ� ����ǰ��ѭ�� �� ����ֵ��һѭ�� ֮ǰ���������ų��ֵ�
	G.vexnum--;
	return OK;
}//DeleteVex

Status InsertEdge(AMLGraph& G, char v, char w) {
	//����ͼG�в����(v,w)
	int i = LocateVex(G, v);
	int j = LocateVex(G, w);
	EBox* p = G.adjmulist[i].firstedge;
	while (p) {
		if (p->ivex == j || p->jvex == j) return ERROR;//���Ѵ���
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
	//����ͼG��ɾ����(v,w)
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
		if (!p) return ERROR;//�߲�����
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
		if (!p) return ERROR;//�߲�����
		if (pre->ivex == j)
			pre->ilink = p->ivex == j ? p->ilink : p->jlink;
		else
			pre->jlink = p->ivex == j ? p->ilink : p->jlink;
	}
	free(p);
	G.arcnum--;
	return OK;
}//DeleteEdge

/*ͼ�����ֱ���*/

Status DFSTraverse(MGraph G, Status(*visit)(char a)) {
	//��ͼG��������ȱ������洢�ṹΪ�ڽӾ���
	VisitFunc = visit;
	for (int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;//��ʼ����־����
	for (int i = 0; i < G.vexnum; ++i)
		if (!visited[i])
			DFS(G, i);
	return OK;
}//DFSTraverse

Status DFS(MGraph G, int i) {
	//��λ��Ϊi�Ķ������������ȱ���
	visited[i] = TRUE;
	if (!(*VisitFunc)(G.vexs[i])) return ERROR;
	for (int j = FirstAdjVex(G, G.vexs[i]); j >= 0; j = NextAdjVex(G, G.vexs[i], G.vexs[j]))
		if (!visited[j]) DFS(G, j);
	return OK;
}//DFS

Status DFSTraverse(ALGraph G, Status(*visit)(char a)) {
	//��ͼG��������ȱ������洢�ṹΪ�ڽӾ���
	VisitFunc = visit;
	for (int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;//��ʼ����־����
	for (int i = 0; i < G.vexnum; ++i)
		if (!visited[i])
			DFS(G, i);
	return OK;
}//DFSTraverse

Status DFS(ALGraph G, int i) {
	//��λ��Ϊi�Ķ������������ȱ���
	visited[i] = TRUE;
	if (!(*VisitFunc)(G.vertices[i].data)) return ERROR;
	for (int j = FirstAdjVex(G, G.vertices[i].data); j >= 0; j = NextAdjVex(G, G.vertices[i].data, G.vertices[j].data))
		if (!visited[j]) DFS(G, j);
	return OK;
}//DFS

Status DFSTraverse(OLGraph G, Status(*visit)(char a)) {
	//��ͼG��������ȱ������洢�ṹΪ�ڽӾ���
	VisitFunc = visit;
	for (int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;//��ʼ����־����
	for (int i = 0; i < G.vexnum; ++i)
		if (!visited[i])
			DFS(G, i);
	return OK;
}//DFSTraverse

Status DFS(OLGraph G, int i) {
	//��λ��Ϊi�Ķ������������ȱ���
	visited[i] = TRUE;
	if (!(*VisitFunc)(G.xlist[i].data)) return ERROR;
	for (int j = FirstOutVex(G, G.xlist[i].data); j >= 0; j = NextOutVex(G, G.xlist[i].data, G.xlist[j].data))
		if (!visited[j]) DFS(G, j);
	return OK;
}//DFS

Status DFSTraverse(AMLGraph G, Status(*visit)(char a)) {
	//��ͼG��������ȱ������洢�ṹΪ�ڽӾ���
	VisitFunc = visit;
	for (int i = 0; i < G.vexnum; ++i) visited[i] = FALSE;//��ʼ����־����
	for (int i = 0; i < G.vexnum; ++i)
		if (!visited[i])
			DFS(G, i);
	return OK;
}//DFSTraverse

Status DFS(AMLGraph G, int i) {
	//��λ��Ϊi�Ķ������������ȱ���
	visited[i] = TRUE;
	if (!(*VisitFunc)(G.adjmulist[i].data)) return ERROR;
	for (int j = FirstAdjVex(G, G.adjmulist[i].data); j >= 0; j = NextAdjVex(G, G.adjmulist[i].data, G.adjmulist[j].data))
		if (!visited[j]) DFS(G, j);
	return OK;
}//DFS