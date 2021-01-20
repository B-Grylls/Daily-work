# include "String.h"


/*˳��洢���Ļ�����������*/

Status StrAssign(SString& S, const char* chars) {
	//����һ��ֵ�����ַ�������chars�Ĵ�S
	int length = 0;
	int i;
	const char* c = chars;
	for (length = 0; *c; ++length, ++c);//����chars�ĳ��ȣ��ַ�������'\0'��ֵΪ0
	S[0] = length;
	for (i = 1; i <= S[0]; ++i)
		S[i] = *chars++;
	return OK;
}//StrAssign

int StrCompare(SString S, SString T) {
	//��S>T����ֵ����0��S=T����ֵ����0��S<T����ֵС��0
	int i = 1;
	while (i <= S[0] && i <= T[0]) {
		if (S[i] != T[i]) return S[i] - T[i];
		else ++i;
	}
	return S[0] - T[0];
}//StrCompare

int StrLength(SString S) {
	//���ش�S��Ԫ�ظ���
	return S[0];
}//StrLength

Status Concat(SString& T, SString S1, SString S2) {
	//��S1S2���ڣ���T���ض������ӳɵ��´�����δ�ضϷ���TRUE���ضϷ���FALSE
	if (S1[0] + S2[0] <= MAXSTRLEN) {//δ�ض�
		int i;
		T[0] = S1[0] + S2[0];
		for (i = 1; i <= S1[0]; ++i) T[i] = S1[i];
		for (i = S1[0] + 1; i <= S1[0] + S2[0]; ++i) T[i] = S2[i];
		return TRUE;
	}
	else if (S1[0] < MAXSTRLEN) {//�ض���S2��
		int i;
		T[0] = MAXSTRLEN;
		for (i = 1; i <= S1[0]; ++i) T[i] = S1[i];
		for (i = S1[0] + 1; i <= MAXSTRLEN; ++i) T[i] = S2[i];
		return FALSE;
	}
	else {//�ض���S1��
		int i;
		T[0] = MAXSTRLEN;
		for (i = 1; i <= MAXSTRLEN; ++i) T[i] = S1[i];
		return FALSE;
	}
}//Concat

Status SubStr(SString& Sub, SString S, int pos, int len) {
	//��Sub���ش�S�е�pos���ַ��𳤶�Ϊlen���Ӵ�
	//�Ϸ�����1<=pos<=StrLength(S),0<=len<=StrLength(S)-pos+1
	if (pos<1 || pos>S[0] || len<0 || len>S[0] - pos + 1)
		return ERROR;//�Ƿ�
	Sub[0] = len;
	for (int i = 1; i <= len; ++i) Sub[i] = S[i + pos - 1];
	return OK;
}//SubStr

Status ClearStr(SString& S) {
	//��մ�
	S[0] = 0;
	return OK;
}//ClearStr

Status StrCopy(SString& T, SString S) {
	//����S���Ƹ�T
	//Ҳ����ͨ��Concat�����������
	T[0] = S[0];
	for (int i = 1; i <= S[0]; ++i)
		T[i] = S[i];
	return OK;
}//StrCopy

Status StrEmpty(SString S) {
	//�жϴ�S�Ƿ�Ϊ��
	//Ҳ����ͨ��StrCompare�����������
	if (StrLength(S) == 0) return TRUE;
	else return FALSE;
}//StrEmpty

/*���ĸ��ϲ��������Խ����ڻ�����������ɣ�*/
int Index(SString S, SString T, int pos) {
	//��S��T���ڣ�T�ǿգ���S�д�����Tֵ��ͬ���Ӵ�����������S�е�pos���ַ���(����pos)��һ�γ��ֵ�λ��
	//���򷵻�0���Ϸ�����1<=pos<=StrLength(S)
	if (pos<1 || pos>StrLength(S)) return 0;
	int n = StrLength(S), m = StrLength(T);
	int i = pos;
	while (i <= n - m + 1) {
		SString sub;
		SubStr(sub, S, i, m);
		if (StrCompare(sub, T) != 0) ++i;
		else return i;
	}
	return 0;
}//Index

Status Replace(SString& S, SString T, SString V) {
	//�ô�V�滻S�г��ֵ�������T����Ҳ��ص����Ӵ�
	if (!StrLength(T)) return ERROR;//��TΪ�գ��޴��滻
	int pos = 1;
	SString X, Y = { 0 };
	int s = StrLength(S), t = StrLength(T), v = StrLength(V);
	while (Index(S, T, pos)) {
		int i = Index(S, T, pos);
		SubStr(X, S, 1, i - 1);
		SubStr(Y, S, i + t, s - i - t + 1);
		Concat(S, X, V);
		Concat(S, S, Y);
		pos = i + v;
	}
	return OK;
}//Replace

Status StrInsert(SString& S, int pos, SString T) {
	//�ڴ�S�ĵ�pos���ַ�ǰ���봮T
	//�Ϸ�����1<=pos<=StrLength(S)+1
	if (pos<1 || pos>StrLength(S) + 1) return ERROR;
	int s = StrLength(S);
	SString X, Y = { 0 };
	SubStr(X, S, 1, pos - 1);
	SubStr(Y, S, pos, s - pos + 1);//���pos<sԽ�磬SubStr����ERROR��YΪ��
	Concat(S, X, T);
	Concat(S, S, Y);
	return OK;
}//StrInsert

Status StrDelete(SString& S, int pos, int len) {
	//�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
	//�Ϸ�����1<=pos<=StrLength(S),0<=len<=StrLength(S)-pos+1
	if (pos<1 || pos>StrLength(S) || len<0 || len>StrLength(S) - pos + 1) return ERROR;
	int s = StrLength(S);
	SString X, Y = { 0 };
	SubStr(X, S, 1, pos - 1);
	SubStr(Y, S, pos + len, s - pos - len + 1);//���pos+len>sԽ�磬SubStrֱ�ӷ���ERROR��YΪ��
	Concat(S, X, Y);
	return OK;
}//StrDelete

/*�Ѵ洢���Ļ�����������*/

Status StrAssign(HString& S, const char* chars) {
	//����һ��ֵΪchars�Ĵ�
	if (S.ch) free(S.ch);//�ͷ�S��ԭ�пռ�
	int length = 0;
	const char* c = chars;
	for (; *c; ++c, ++length);//��chars����
	if (!length) {
		S.ch = NULL; S.length = 0;
	}
	else {
		S.ch = (char*)malloc(length * sizeof(char));
		if (!S.ch) exit(OVERFLOW);
		for (int i = 0; i < length; ++i)
			S.ch[i] = chars[i];
		S.length = length;
	}
	return OK;
}//StrAssign

int StrCompare(HString S, HString T) {
	//��S>T����ֵ����0��S=T����ֵ����0��S<T����ֵС��0
	int i = 0;
	while (i <= S.length - 1 && i <= T.length - 1) {
		if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
		else i++;
	}
	return S.length - T.length;
}//StrCompare

int StrLength(HString S) {
	//���ش���
	return S.length;
}//StrLength

Status ClearStr(HString& S) {
	//��մ�,���ͷ���ռ�
	if (S.ch) {
		free(S.ch);
		S.ch = NULL;
	}
	S.length = 0;
	return OK;
}//ClearStr

Status Concat(HString& T, HString S1, HString S2) {
	//��T����S1��S2���Ӷ��ɵ��´�
	if (T.ch) free(T.ch);
	T.ch = (char*)malloc((S1.length + S2.length) * sizeof(char));
	if (!T.ch) exit(OVERFLOW);
	for (int i = 0; i < S1.length; ++i)
		T.ch[i] = S1.ch[i];
	for (int i = 0; i < S2.length; ++i)
		T.ch[i + S1.length] = S2.ch[i];
	T.length = S1.length + S2.length;
	if (!T.length) { free(T.ch); T.ch = NULL; }//���TΪ�գ���malloc�����0�ڴ����ͷŲ�ָ��NULL
	return OK;
}//Concat

Status SubStr(HString& Sub, HString S, int pos, int len) {
	//��Sub���ش�S�е�pos���ַ��𳤶�Ϊlen���Ӵ�
	//�Ϸ�����1<=pos<=StrLength(S),0<=len<=StrLength(S)-pos+1
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;//�Ƿ�
	if (Sub.ch) free(Sub.ch);//�ͷž��ڴ�
	if (!len) {
		Sub.ch = NULL; Sub.length = 0;
	}
	else {
		Sub.ch = (char*)malloc(len * sizeof(char));
		if (!Sub.ch) exit(OVERFLOW);
		Sub.length = len;
		for (int i = 0; i < len; ++i)
			Sub.ch[i] = S.ch[pos + i - 1];
	}
	return OK;
}//SubString

/*���ĸ��ϲ��������Խ����ڻ�����������ɣ�*/

int Index(HString S, HString T, int pos) {
	//��S��T���ڣ�T�ǿգ���S�д�����Tֵ��ͬ���Ӵ�����������S�е�pos���ַ���(����pos)��һ�γ��ֵ�λ��
	//���򷵻�0���Ϸ�����1<=pos<=StrLength(S)
	if (pos<1 || pos>StrLength(S)) return 0;
	int n = StrLength(S), m = StrLength(T);
	int i = pos;
	while (i <= n - m + 1) {
		HString sub;
		SubStr(sub, S, i, m);
		if (StrCompare(sub, T) != 0) ++i;
		else return i;
	}
	return 0;
}//Index

Status Replace(HString& S, HString T, HString V) {
	//�ô�V�滻S�г��ֵ�������T����Ҳ��ص����Ӵ�
	if (!StrLength(T)) return ERROR;//��TΪ�գ��޴��滻
	int pos = 1;
	HString X, Y, Z;
	X.ch = Y.ch = Z.ch = NULL;
	X.length = Y.length = Z.length = 0;
	int s = StrLength(S), t = StrLength(T), v = StrLength(V);
	while (Index(S, T, pos)) {
		int i = Index(S, T, pos);
		SubStr(X, S, 1, i - 1);
		SubStr(Y, S, i + t, s - i - t + 1);
		Concat(Z, X, V);
		Concat(S, Z, Y);//���ﲻ����S,S,Y���֣�concat���ڵ�һ��free(S)
		pos = i + v;
	}
	return OK;
}//Replace

Status StrInsert(HString& S, int pos, HString T) {
	//�ڴ�S�ĵ�pos���ַ�ǰ���봮T
	//�Ϸ�����1<=pos<=StrLength(S)+1
	if (pos<1 || pos>StrLength(S) + 1) return ERROR;
	int s = StrLength(S);
	HString X, Y, Z;
	X.ch = Y.ch = Z.ch = NULL;
	X.length = Y.length = Z.length = 0;
	SubStr(X, S, 1, pos - 1);
	SubStr(Y, S, pos, s - pos + 1);//���pos<sԽ�磬SubStr����ERROR��YΪ��
	Concat(Z, X, T);
	Concat(S, Z, Y);
	return OK;
}//StrInsert

Status StrDelete(HString& S, int pos, int len) {
	//�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
	//�Ϸ�����1<=pos<=StrLength(S),0<=len<=StrLength(S)-pos+1
	if (pos<1 || pos>StrLength(S) || len<0 || len>StrLength(S) - pos + 1) return ERROR;
	int s = StrLength(S);
	HString X, Y;
	X.ch = Y.ch = NULL;
	X.length = Y.length = 0;
	SubStr(X, S, 1, pos - 1);
	SubStr(Y, S, pos + len, s - pos - len + 1);//���pos+len>sԽ�磬SubStrֱ�ӷ���ERROR��YΪ��
	Concat(S, X, Y);
	return OK;
}//StrDelete