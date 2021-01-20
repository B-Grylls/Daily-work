# include "Search Table.h"

/*�ȽϺ���*/

Status EQ(KeyType a, KeyType b) {
	//�б����
	if (a == b) return TRUE;
	else return FALSE;
}//EQ

Status LT(KeyType a, KeyType b) {
	//�б�С��
	if (a < b) return TRUE;
	else return FALSE;
}//LT

Status LQ(KeyType a, KeyType b) {
	//�б�С�ڵ���
	if (a <= b) return TRUE;
	else return FALSE;
}//LQ

Status RT(KeyType a, KeyType b) {
	//�б����
	if (a > b) return TRUE;
	else return FALSE;
}//RT

Status RQ(KeyType a, KeyType b) {
	//�б���ڵ���
	if (a >= b) return TRUE;
	else return FALSE;
}//RQ

/*��̬���ұ���*/

Status CreateSST(SSTable& ST) {
	//����һ��n������Ԫ�صľ�̬���ұ�ST��0��λ��Ϊ�ж�λ
	int n;
	printf("enter the quantity of data:");
	scanf_s("%d", &n);
	ST.elem = (STElemType*)malloc((n + 1) * sizeof(STElemType));
	if (!ST.elem) return ERROR;
	ST.length = n;
	printf("weight exist?  Y-1  N-0\n");
	scanf_s("%d", &ST.elem[0].weight);
	printf("enter data by order\n");
	for (int i = 1; i <= n; ++i) {
		scanf_s(" %c", &ST.elem[i].key);
		if (ST.elem[0].weight)
			scanf_s("%d", &ST.elem[i].weight);
	}
	return OK;
}//CreateSST

Status DestroySST(SSTable& ST) {
	//���پ�̬���ұ�ST
	ST.length = 0;
	free(ST.elem);
	ST.elem = NULL;
	return OK;
}//DestroySST

Status TraverseSST(SSTable& ST) {
	//��˳�����������ұ��е�keyֵ����Ȩ��Ҳ���Ȩ��
	//��ʱ����visit����ָ�룬����Ҫ�����޸ģ�����Ϊ��������ӹ���
	for (int i = 1; i <= ST.length; ++i)
		printf("%3c", ST.elem[i].key);
	printf("\n");
	if (ST.elem[0].weight)
		for (int i = 1; i <= ST.length; ++i)
			printf("%3d", ST.elem[i].weight);
	return OK;
}//TraverseSST

int Search_Seq(SSTable ST, KeyType key) {
	//�����˳�����
	ST.elem[0].key = key;
	int i = ST.length;
	while (!EQ(ST.elem[0].key, key))
		--i;
	return i;
}//Search_Seq

int Search_Bin(SSTable ST, KeyType key) {
	//������۰����
	int low = 1, high = ST.length;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (EQ(ST.elem[mid].key, key)) return mid;
		else if (LT(key, ST.elem[mid].key)) high = mid - 1;
		else low = mid + 1;
	}
	return 0;//δ�ҵ�
}//Search_Bin

int Search_intpo(SSTable ST, KeyType key) {
	//������ֵ����
	int low = 1, high = ST.length;
	while (low <= high) {
		int i = (key - ST.elem[low].key) * (high - low + 1) / (ST.elem[high].key - ST.elem[low].key);
		if (EQ(ST.elem[i].key, key)) return i;
		else if (LT(key, ST.elem[i].key)) high = i - 1;
		else low = i + 1;
	}
	return 0;
}//Search_intpo

Status CreateSOSTree(SOSTree& T, SSTable ST, int sw[]) {
	//����������ɴ��Ų�������sw�����ۻ�Ȩֵ��
	if (ST.length == 0) T = NULL;
	else {
		int temp = 0;
		sw[0] = 0;
		for (int j = 1; j <= ST.length; ++j) {//��ʼ��sw
			temp += ST.elem[j].weight;
			sw[j] = temp;
		}
		SecondOptimal(T, ST, sw, 1, ST.length);
	}
	return OK;
}//CreateSOSTree

Status SecondOptimal(BiTree& T, SSTable R, int sw[], int low, int high) {
	//CreateSOSTree���ݹ麯����sw��¼�����R�е��ۻ�Ȩ�أ�low high������
	int i = low, min = abs(sw[high] - sw[low]), dw = sw[high] + sw[low - 1];
	for (int j = low + 1; j <= high; ++j)//��Ѱ��СPi
		if (abs(dw - sw[j] - sw[j - 1]) < min) {
			min = abs(dw - sw[j] - sw[j - 1]); i = j;
		}
	T = (BiTNode*)malloc(sizeof(BiTNode));
	if (!T) return ERROR;
	T->data = R.elem[i].key;
	T->lchild = T->rchild = NULL;
	if (i != low)
		SecondOptimal(T->lchild, R, sw, low, i - 1);//����������
	if (i != high) {
		int temp = 0;
		sw[i] = 0;
		for (int j = i + 1; j <= high; ++j) {//�����޸ĸ�λsw��ֵ
			temp += R.elem[j].weight;
			sw[j] = temp;
		}
		SecondOptimal(T->rchild, R, sw, i + 1, high);//����������
	}
	return OK;
}//SecondOptimal

BiTNode* Search_SOSTree(SOSTree T, KeyType key) {
	//�Դ��Ų��������бȽϣ������ҵ��Ľ�㣬���򷵻ؿ�
	//����Ҫ������������е�λ�ã������½�BiTNode�е���index���ڴ���SOSTreeʱ��¼
	if (!T) return NULL;//key�����������
	if (EQ(T->data, key)) return T;//�ҵ�keyλ��
	else if (LT(key, T->data)) return Search_SOSTree(T->lchild, key);
	else return Search_SOSTree(T->rchild, key);
}//Search_SOSTree

/*��̬���ұ��������������*/
/*BSTree==BiTree*/

Status InitBST(BSTree& T) {
	//��ʼ���ն�̬���ұ�
	T = NULL;
	return OK;
}//InitDSTable

Status DestroyBST(BSTree& T) {
	//���ٶ�̬���ұ�
	if (!T) return OK;
	DestroyBST(T->lchild);
	DestroyBST(T->rchild);
	free(T);
	return OK;
}//DestroyBST

Status SearchBST(BSTree T, KeyType key, BiTNode* f, BiTNode*& p) {
	//�ڶ���������T������keyֵ��pָ����Ӧ��㣬����������ָ���
	//fָ���ʼָ��T��parent����key����T��ʱ��p����ͣ������Ҫ����ط���parent��
	if (!T) { p = f; return FALSE; }//����ʧ��
	if (EQ(T->data, key)) { p = T; return TRUE; }//���ҳɹ�
	else if (LT(key, T->data)) return SearchBST(T->lchild, key, T, p);
	else return SearchBST(T->rchild, key, T, p);
}//SearchBST

Status InsertBST(BSTree& T, STElemType e) {
	//�ڶ���������T�в���e������e.key��ֵ�����в�����
	BiTNode* p;
	if (!SearchBST(T, e.key, NULL, p)) {
		BiTNode* s = (BiTNode*)malloc(sizeof(BiTNode));
		if (!s) return ERROR;
		s->data = e.key;
		s->lchild = s->rchild = NULL;
		if (!T) T = s;
		else if (LT(e.key, p->data)) p->lchild = s;
		else p->rchild = s;
		return TRUE;
	}
	else return FALSE;
}//InsertBST

Status DeleteBST(BSTree& T, KeyType key) {
	//ɾ��������������keyֵΪkey�Ľ��,fָ��T��parent
	if (!T) return FALSE;
	else {
		if (EQ(T->data, key)) return DeleteBSNode(T);
		else if (LT(key, T->data)) return DeleteBST(T->lchild, key);
		else return DeleteBST(T->rchild, key);
	}
}//DeleteBST

Status DeleteBSNode(BiTNode*& p) {
	//DeleteBST�������Ӻ���������ɾ�������������еĽ��p���ұ��ֶ������������ʲ��䣬����fΪp��parent
	BiTNode* q=p;
	if (!p->lchild) {
		p = p->rchild;
		free(q);
	}
	else if (!p->rchild) {
		p = p->lchild;
		free(q);
	}
	else {//��������������
		BiTNode* s = p->lchild;
		while (s->rchild) {//sָ��pǰ����qΪs��parent
			q = s; s = s->rchild;
		}
		p->data = s->data;
		if (q != p) q->rchild = s->lchild;
		else q->lchild = s->lchild;
		free(s);
	}
	return OK;
}//DeleteBSNode

Status InsertAVL(BSTree& T, STElemType e, bool& taller) {
	//���ж�ƽ�������T��������e.key��ͬ�Ľ�㣬����з���FALSE
	//���û�оͲ���e����ͨ��������֤��������ƽ�⣬����TRUE
	//taller������T�������ߣ���Ϊ�޸�ƽ������bf������
	if (!T) {//�������
		T = (BiTNode*)malloc(sizeof(BiTNode));
		if (!T) return ERROR;
		T->data = e.key; T->flag = EH;
		T->lchild = T->rchild = NULL;
		taller = TRUE;
	}
	else {
		if (EQ(T->data, e.key)) {//������
			taller = FALSE; return FALSE;
		}
		else if (LT(e.key, T->data)) {//��Ѱ�����������
			if (!InsertAVL(T->lchild, e, taller)) return FALSE;//��ಢδ����½��
			if (taller) //������½�㣬�Ҷ��ڵ�ǰ���T��˵����������������
				switch (T->flag) {
				case LH:LeftBalance(T); taller = FALSE; break;
				case EH:T->flag = LH; taller = TRUE; break;
				case RH:T->flag = EH; taller = FALSE; break;
				}
		}
		else {
			if (!InsertAVL(T->rchild, e, taller)) return FALSE;//�Ҳಢδ����½��
			if (taller) {//������½�㣬�Ҷ��ڵ�ǰ���T��˵����������������
				switch (T->flag) {
				case LH:T->flag = EH; taller = FALSE; break;
				case EH:T->flag = RH; taller = TRUE; break;
				case RH:RightBalance(T); taller = FALSE; break;
				}
			}
		}
	}
	return TRUE;
}//InsertAVL

Status LeftBalance(BSTree& T) {
	//�²�������T���������ϣ���T�Ǿ����������ʧȥƽ��Ľ�㣬ͨ������ʹƽ��ָ�����֮Ϊ��ƽ��
	BiTNode* lc = T->lchild;
	if (lc->flag == LH) {//�½����lc���������ϣ���ȡ��������T����
		T->flag = lc->flag = EH;//�޸�balance factor
		R_Rotate(T);
		T = lc;
	}
	else {//�½����lc���������ϣ���ȡ������lc������T����
		BiTNode* rd = lc->rchild;
		switch (rd->flag ) {//���������bfֵ�޸Ĳ�һ��
		case LH:T->flag = RH; lc->flag = EH; break;
		case RH:T->flag = EH; lc->flag = LH; break;
		case EH:T->flag = lc->flag = EH; break;//������©��rd�п������¼���Ľ��
		}
		rd->flag = EH;
		L_Rotate(T->lchild);//�˴���������ΪT��أ���������lcָ�룬��ΪRotate�ĺ����Ĺؼ������ڷ���ָ����޸�
		R_Rotate(T);
	}
	return OK;
}//LeftBalance

Status RightBalance(BSTree& T) {
	//�²�������T���������ϣ���T�Ǿ����������ʧȥƽ��Ľ�㣬ͨ������ʹƽ��ָ�����֮Ϊ��ƽ��
	BiTNode* rc = T->rchild;
	if (rc->flag == RH) {//�½����rc���������ϣ���ȡ��������T����
		T->flag = rc->flag = EH;//�޸�balance factor
		L_Rotate(T);
		T = rc;
	}
	else {//�½����rc���������ϣ���ȡ������rc������T����
		BiTNode* ld = rc->lchild;
		switch (ld->flag) {//���������bfֵ�޸Ĳ�һ��
		case LH:T->flag = EH; rc->flag = RH; break;
		case RH:T->flag = LH; rc->flag = EH; break;
		case EH:T->flag = rc->flag = EH; break;//������©��rd�п������¼���Ľ��
		}
		ld->flag = EH;
		R_Rotate(T->rchild);//�˴���������ΪT��أ���������rcָ�룬��ΪRotate�ĺ����Ĺؼ������ڷ���ָ����޸�
		L_Rotate(T);
	}
	return OK;
}//RightBalance

Status R_Rotate(BSTree& p) {
	//InsertAVL�������Ӻ��������ã���������p����ʹ��p->lchild��Ϊ��Ϊ�µĸ��ڵ㣬��ʹpָ����
	BiTNode* lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
	return OK;
}//R_Rotate

Status L_Rotate(BSTree& p) {
	//InsertAVL�������Ӻ��������ã���������p����ʹ��p->rchild��Ϊ��Ϊ�µĸ��ڵ㣬��ʹpָ����
	BiTNode* rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
	return OK;
}//L_Rotate
