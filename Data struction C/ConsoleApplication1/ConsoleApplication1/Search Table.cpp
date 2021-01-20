# include "Search Table.h"

/*比较函数*/

Status EQ(KeyType a, KeyType b) {
	//判别相等
	if (a == b) return TRUE;
	else return FALSE;
}//EQ

Status LT(KeyType a, KeyType b) {
	//判别小于
	if (a < b) return TRUE;
	else return FALSE;
}//LT

Status LQ(KeyType a, KeyType b) {
	//判别小于等于
	if (a <= b) return TRUE;
	else return FALSE;
}//LQ

Status RT(KeyType a, KeyType b) {
	//判别大于
	if (a > b) return TRUE;
	else return FALSE;
}//RT

Status RQ(KeyType a, KeyType b) {
	//判别大于等于
	if (a >= b) return TRUE;
	else return FALSE;
}//RQ

/*静态查找表函数*/

Status CreateSST(SSTable& ST) {
	//创建一个n个数据元素的静态查找表ST，0号位作为判断位
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
	//销毁静态查找表ST
	ST.length = 0;
	free(ST.elem);
	ST.elem = NULL;
	return OK;
}//DestroySST

Status TraverseSST(SSTable& ST) {
	//按顺序遍历输出查找表中的key值，有权重也输出权重
	//暂时不用visit函数指针，如需要可以修改，这里为了输出更加规整
	for (int i = 1; i <= ST.length; ++i)
		printf("%3c", ST.elem[i].key);
	printf("\n");
	if (ST.elem[0].weight)
		for (int i = 1; i <= ST.length; ++i)
			printf("%3d", ST.elem[i].weight);
	return OK;
}//TraverseSST

int Search_Seq(SSTable ST, KeyType key) {
	//无序表顺序查找
	ST.elem[0].key = key;
	int i = ST.length;
	while (!EQ(ST.elem[0].key, key))
		--i;
	return i;
}//Search_Seq

int Search_Bin(SSTable ST, KeyType key) {
	//有序表折半查找
	int low = 1, high = ST.length;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (EQ(ST.elem[mid].key, key)) return mid;
		else if (LT(key, ST.elem[mid].key)) high = mid - 1;
		else low = mid + 1;
	}
	return 0;//未找到
}//Search_Bin

int Search_intpo(SSTable ST, KeyType key) {
	//有序表插值查找
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
	//从有序表生成次优查找树，sw辅助累积权值表
	if (ST.length == 0) T = NULL;
	else {
		int temp = 0;
		sw[0] = 0;
		for (int j = 1; j <= ST.length; ++j) {//初始化sw
			temp += ST.elem[j].weight;
			sw[j] = temp;
		}
		SecondOptimal(T, ST, sw, 1, ST.length);
	}
	return OK;
}//CreateSOSTree

Status SecondOptimal(BiTree& T, SSTable R, int sw[], int low, int high) {
	//CreateSOSTree主递归函数，sw记录有序表R中的累积权重，low high下上限
	int i = low, min = abs(sw[high] - sw[low]), dw = sw[high] + sw[low - 1];
	for (int j = low + 1; j <= high; ++j)//搜寻最小Pi
		if (abs(dw - sw[j] - sw[j - 1]) < min) {
			min = abs(dw - sw[j] - sw[j - 1]); i = j;
		}
	T = (BiTNode*)malloc(sizeof(BiTNode));
	if (!T) return ERROR;
	T->data = R.elem[i].key;
	T->lchild = T->rchild = NULL;
	if (i != low)
		SecondOptimal(T->lchild, R, sw, low, i - 1);//构造左子树
	if (i != high) {
		int temp = 0;
		sw[i] = 0;
		for (int j = i + 1; j <= high; ++j) {//重新修改高位sw的值
			temp += R.elem[j].weight;
			sw[j] = temp;
		}
		SecondOptimal(T->rchild, R, sw, i + 1, high);//构造右子树
	}
	return OK;
}//SecondOptimal

BiTNode* Search_SOSTree(SOSTree T, KeyType key) {
	//以次优查找树进行比较，返回找到的结点，否则返回空
	//若需要返回在有序表中的位置，可以新建BiTNode中的域index来在创建SOSTree时记录
	if (!T) return NULL;//key不在有序表中
	if (EQ(T->data, key)) return T;//找到key位置
	else if (LT(key, T->data)) return Search_SOSTree(T->lchild, key);
	else return Search_SOSTree(T->rchild, key);
}//Search_SOSTree

/*动态查找表二叉排序树函数*/
/*BSTree==BiTree*/

Status InitBST(BSTree& T) {
	//初始化空动态查找表
	T = NULL;
	return OK;
}//InitDSTable

Status DestroyBST(BSTree& T) {
	//销毁动态查找表
	if (!T) return OK;
	DestroyBST(T->lchild);
	DestroyBST(T->rchild);
	free(T);
	return OK;
}//DestroyBST

Status SearchBST(BSTree T, KeyType key, BiTNode* f, BiTNode*& p) {
	//在二叉排序树T中搜索key值，p指向相应结点，若不存在则指向空
	//f指针初始指向T的parent，当key不在T中时，p最终停留在需要插入地方的parent处
	if (!T) { p = f; return FALSE; }//查找失败
	if (EQ(T->data, key)) { p = T; return TRUE; }//查找成功
	else if (LT(key, T->data)) return SearchBST(T->lchild, key, T, p);
	else return SearchBST(T->rchild, key, T, p);
}//SearchBST

Status InsertBST(BSTree& T, STElemType e) {
	//在二叉排序树T中插入e，其中e.key的值在树中不存在
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
	//删除二叉排序树中key值为key的结点,f指向T的parent
	if (!T) return FALSE;
	else {
		if (EQ(T->data, key)) return DeleteBSNode(T);
		else if (LT(key, T->data)) return DeleteBST(T->lchild, key);
		else return DeleteBST(T->rchild, key);
	}
}//DeleteBST

Status DeleteBSNode(BiTNode*& p) {
	//DeleteBST的主体子函数，用来删除二叉排序树中的结点p，且保持二叉排序树性质不变，其中f为p的parent
	BiTNode* q=p;
	if (!p->lchild) {
		p = p->rchild;
		free(q);
	}
	else if (!p->rchild) {
		p = p->lchild;
		free(q);
	}
	else {//左右子树均不空
		BiTNode* s = p->lchild;
		while (s->rchild) {//s指向p前驱，q为s的parent
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
	//先判断平衡二叉树T中有无与e.key相同的结点，如果有返回FALSE
	//如果没有就插入e，并通过调整保证二叉树的平衡，返回TRUE
	//taller代表树T有无增高，作为修改平衡因子bf的依据
	if (!T) {//新增结点
		T = (BiTNode*)malloc(sizeof(BiTNode));
		if (!T) return ERROR;
		T->data = e.key; T->flag = EH;
		T->lchild = T->rchild = NULL;
		taller = TRUE;
	}
	else {
		if (EQ(T->data, e.key)) {//结点存在
			taller = FALSE; return FALSE;
		}
		else if (LT(e.key, T->data)) {//搜寻过程走向左侧
			if (!InsertAVL(T->lchild, e, taller)) return FALSE;//左侧并未添加新结点
			if (taller) //添加了新结点，且对于当前结点T来说，其左子树长高了
				switch (T->flag) {
				case LH:LeftBalance(T); taller = FALSE; break;
				case EH:T->flag = LH; taller = TRUE; break;
				case RH:T->flag = EH; taller = FALSE; break;
				}
		}
		else {
			if (!InsertAVL(T->rchild, e, taller)) return FALSE;//右侧并未添加新结点
			if (taller) {//添加了新结点，且对于当前结点T来说，其右子树长高了
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
	//新插入结点在T的左子树上，且T是距离其最近的失去平衡的结点，通过调整使平衡恢复，称之为左平衡
	BiTNode* lc = T->lchild;
	if (lc->flag == LH) {//新结点在lc的左子树上，采取单次右旋T策略
		T->flag = lc->flag = EH;//修改balance factor
		R_Rotate(T);
		T = lc;
	}
	else {//新结点在lc的右子树上，采取先左旋lc再右旋T策略
		BiTNode* rd = lc->rchild;
		switch (rd->flag ) {//三种情况的bf值修改不一样
		case LH:T->flag = RH; lc->flag = EH; break;
		case RH:T->flag = EH; lc->flag = LH; break;
		case EH:T->flag = lc->flag = EH; break;//不能遗漏，rd有可能是新加入的结点
		}
		rd->flag = EH;
		L_Rotate(T->lchild);//此处参数必须为T相关，而不能用lc指针，因为Rotate的函数的关键就在于返回指针的修改
		R_Rotate(T);
	}
	return OK;
}//LeftBalance

Status RightBalance(BSTree& T) {
	//新插入结点在T的右子树上，且T是距离其最近的失去平衡的结点，通过调整使平衡恢复，称之为右平衡
	BiTNode* rc = T->rchild;
	if (rc->flag == RH) {//新结点在rc的右子树上，采取单次左旋T策略
		T->flag = rc->flag = EH;//修改balance factor
		L_Rotate(T);
		T = rc;
	}
	else {//新结点在rc的左子树上，采取先右旋rc再左旋T策略
		BiTNode* ld = rc->lchild;
		switch (ld->flag) {//三种情况的bf值修改不一样
		case LH:T->flag = EH; rc->flag = RH; break;
		case RH:T->flag = LH; rc->flag = EH; break;
		case EH:T->flag = rc->flag = EH; break;//不能遗漏，rd有可能是新加入的结点
		}
		ld->flag = EH;
		R_Rotate(T->rchild);//此处参数必须为T相关，而不能用rc指针，因为Rotate的函数的关键就在于返回指针的修改
		L_Rotate(T);
	}
	return OK;
}//RightBalance

Status R_Rotate(BSTree& p) {
	//InsertAVL函数的子函数，作用：单次右旋p树，使得p->lchild成为成为新的根节点，并使p指向它
	BiTNode* lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
	return OK;
}//R_Rotate

Status L_Rotate(BSTree& p) {
	//InsertAVL函数的子函数，作用：单次左旋p树，使得p->rchild成为成为新的根节点，并使p指向它
	BiTNode* rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
	return OK;
}//L_Rotate
