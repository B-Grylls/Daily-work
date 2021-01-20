# include <stdio.h>
# include <stdlib.h>
# define MAXLSIZE 1000
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0

typedef int Status;
typedef struct {//��̬����
	int data;//������
	int cur;//ָ����
}component, SLinkList[MAXLSIZE];


int LocateElem_SL(SLinkList S, int e) {
	//���ص�һ����e��ȵ�Ԫ�ص��±꣬�����򷵻�0
	int i = S[0].cur;//ָ���һ���ڵ��ָ��
	while (i && S[i].data != e)
		i = S[i].cur;
	return i;
}//LocateElem_SL

Status InitList_SL(SLinkList& S) {
	//��ʼ��һ����СΪMAXSIZE�ľ�̬����S[0].curΪͷָ��
	int i;
	for (i = 0; i < MAXLSIZE - 1; ++i)
		S[i].cur = i + 1;
	S[MAXLSIZE - 1].cur = 0;
	return OK;
}//InitList_SL

int Malloc_SL(SLinkList& Space) {
	//��S��ȡ����һ���ڵ㣨S[0].curָ��ģ�������λ��ֵi,i=0��ʾΪ�ձ��޷�ȡ����Sͨ��Ϊ��������
	int i = Space[0].cur;
	if (i) Space[0].cur = Space[i].cur;
	return i;
}//Malloc_SL

Status Free_SL(SLinkList& Space, int k) {
	//���±�Ϊk�Ľ���ջر���������
	Space[k].cur = Space[0].cur;
	Space[0].cur = k;
	return OK;
}//Free_SL

void difference(SLinkList& S, int& sp) {
	//��һά����S�д������ϣ�A-B���ȣ�B-A���ľ�̬��������ͷָ��Ϊsp��ָ��ͷ��㣬βָ��Ϊr����������ͷָ��ΪS[0].cur
	InitList_SL(S);
	int m, n;//A B��Ԫ�ظ���
	int i;
	int t;//����ȡ����ָ��
	sp = Malloc_SL(S);//����ͷָ��
	int r = sp;//��ͨ������A��Ԫ���ƶ���Ϊβָ��
	scanf_s("%d%d", &m, &n);
	for (i = 1; i <= m; ++i) {//������AԪ�صľ�̬����,���ݴ��±�2��ʼ
		t = Malloc_SL(S);
		scanf_s("%d", &S[t].data);
		S[r].cur = t;
		r = t;//r����ָ�����һ��Ԫ�س�Ϊβָ��
	}
	S[r].cur = 0;//��β
	for (i = 1; i <= n; ++i) {//��������BԪ�أ���ͬ��ɾ������ͬ�����ӵ���β
		int b;
		scanf_s("%d", &b);
		int p = sp;//ָ��p��k���ڴ�����������û����ͬԪ��
		int k = S[p].cur;//ָ���һ�����
		while (k && S[k].data != b) {
			p = k;
			k = S[k].cur;
		}
		if (k == 0) {//����ͬԪ�أ���β�����½�㣬���ƶ�βָ��
			t = Malloc_SL(S);
			S[t].data = b;
			S[t].cur = S[r].cur;
			S[r].cur = t;
			r = t;
		}
		else {//����ͬԪ�أ�ɾ��
			S[p].cur = S[k].cur;
			Free_SL(S, k);
			if (r == k) r = p;//��ɾ�������һ���Ҫ�ƶ�βָ�뵽ǰһ���
		}
	}
}//difference