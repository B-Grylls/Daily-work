# include "String.h"


/*顺序存储串的基本操作函数*/

Status StrAssign(SString& S, const char* chars) {
	//生成一个值等于字符串常量chars的串S
	int length = 0;
	int i;
	const char* c = chars;
	for (length = 0; *c; ++length, ++c);//计算chars的长度，字符串后有'\0'其值为0
	S[0] = length;
	for (i = 1; i <= S[0]; ++i)
		S[i] = *chars++;
	return OK;
}//StrAssign

int StrCompare(SString S, SString T) {
	//若S>T返回值大于0，S=T返回值等于0，S<T返回值小于0
	int i = 1;
	while (i <= S[0] && i <= T[0]) {
		if (S[i] != T[i]) return S[i] - T[i];
		else ++i;
	}
	return S[0] - T[0];
}//StrCompare

int StrLength(SString S) {
	//返回串S的元素个数
	return S[0];
}//StrLength

Status Concat(SString& T, SString S1, SString S2) {
	//串S1S2存在，由T返回二者连接成的新串，若未截断返回TRUE，截断返回FALSE
	if (S1[0] + S2[0] <= MAXSTRLEN) {//未截断
		int i;
		T[0] = S1[0] + S2[0];
		for (i = 1; i <= S1[0]; ++i) T[i] = S1[i];
		for (i = S1[0] + 1; i <= S1[0] + S2[0]; ++i) T[i] = S2[i];
		return TRUE;
	}
	else if (S1[0] < MAXSTRLEN) {//截断在S2上
		int i;
		T[0] = MAXSTRLEN;
		for (i = 1; i <= S1[0]; ++i) T[i] = S1[i];
		for (i = S1[0] + 1; i <= MAXSTRLEN; ++i) T[i] = S2[i];
		return FALSE;
	}
	else {//截断在S1上
		int i;
		T[0] = MAXSTRLEN;
		for (i = 1; i <= MAXSTRLEN; ++i) T[i] = S1[i];
		return FALSE;
	}
}//Concat

Status SubStr(SString& Sub, SString S, int pos, int len) {
	//用Sub返回串S中第pos个字符起长度为len的子串
	//合法输入1<=pos<=StrLength(S),0<=len<=StrLength(S)-pos+1
	if (pos<1 || pos>S[0] || len<0 || len>S[0] - pos + 1)
		return ERROR;//非法
	Sub[0] = len;
	for (int i = 1; i <= len; ++i) Sub[i] = S[i + pos - 1];
	return OK;
}//SubStr

Status ClearStr(SString& S) {
	//清空串
	S[0] = 0;
	return OK;
}//ClearStr

Status StrCopy(SString& T, SString S) {
	//将串S复制给T
	//也可以通过Concat基本操作完成
	T[0] = S[0];
	for (int i = 1; i <= S[0]; ++i)
		T[i] = S[i];
	return OK;
}//StrCopy

Status StrEmpty(SString S) {
	//判断串S是否为空
	//也可以通过StrCompare基本操作完成
	if (StrLength(S) == 0) return TRUE;
	else return FALSE;
}//StrEmpty

/*串的复合操作（可以建立在基础操作上完成）*/
int Index(SString S, SString T, int pos) {
	//串S，T存在，T非空，若S中存在与T值相同的子串，返回其在S中第pos个字符后(包含pos)第一次出现的位置
	//否则返回0，合法输入1<=pos<=StrLength(S)
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
	//用串V替换S中出现的所有与T相等且不重叠的子串
	if (!StrLength(T)) return ERROR;//若T为空，无从替换
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
	//在串S的第pos个字符前插入串T
	//合法输入1<=pos<=StrLength(S)+1
	if (pos<1 || pos>StrLength(S) + 1) return ERROR;
	int s = StrLength(S);
	SString X, Y = { 0 };
	SubStr(X, S, 1, pos - 1);
	SubStr(Y, S, pos, s - pos + 1);//如果pos<s越界，SubStr返回ERROR，Y为空
	Concat(S, X, T);
	Concat(S, S, Y);
	return OK;
}//StrInsert

Status StrDelete(SString& S, int pos, int len) {
	//从串S中删除第pos个字符起长度为len的子串
	//合法输入1<=pos<=StrLength(S),0<=len<=StrLength(S)-pos+1
	if (pos<1 || pos>StrLength(S) || len<0 || len>StrLength(S) - pos + 1) return ERROR;
	int s = StrLength(S);
	SString X, Y = { 0 };
	SubStr(X, S, 1, pos - 1);
	SubStr(Y, S, pos + len, s - pos - len + 1);//如果pos+len>s越界，SubStr直接返回ERROR，Y为空
	Concat(S, X, Y);
	return OK;
}//StrDelete

/*堆存储串的基本操作函数*/

Status StrAssign(HString& S, const char* chars) {
	//生成一个值为chars的串
	if (S.ch) free(S.ch);//释放S的原有空间
	int length = 0;
	const char* c = chars;
	for (; *c; ++c, ++length);//求chars长度
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
	//若S>T返回值大于0，S=T返回值等于0，S<T返回值小于0
	int i = 0;
	while (i <= S.length - 1 && i <= T.length - 1) {
		if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
		else i++;
	}
	return S.length - T.length;
}//StrCompare

int StrLength(HString S) {
	//返回串长
	return S.length;
}//StrLength

Status ClearStr(HString& S) {
	//清空串,并释放其空间
	if (S.ch) {
		free(S.ch);
		S.ch = NULL;
	}
	S.length = 0;
	return OK;
}//ClearStr

Status Concat(HString& T, HString S1, HString S2) {
	//用T返回S1和S2链接而成的新串
	if (T.ch) free(T.ch);
	T.ch = (char*)malloc((S1.length + S2.length) * sizeof(char));
	if (!T.ch) exit(OVERFLOW);
	for (int i = 0; i < S1.length; ++i)
		T.ch[i] = S1.ch[i];
	for (int i = 0; i < S2.length; ++i)
		T.ch[i + S1.length] = S2.ch[i];
	T.length = S1.length + S2.length;
	if (!T.length) { free(T.ch); T.ch = NULL; }//如果T为空，将malloc分配的0内存结点释放并指向NULL
	return OK;
}//Concat

Status SubStr(HString& Sub, HString S, int pos, int len) {
	//用Sub返回串S中第pos个字符起长度为len的子串
	//合法输入1<=pos<=StrLength(S),0<=len<=StrLength(S)-pos+1
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;//非法
	if (Sub.ch) free(Sub.ch);//释放旧内存
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

/*串的复合操作（可以建立在基础操作上完成）*/

int Index(HString S, HString T, int pos) {
	//串S，T存在，T非空，若S中存在与T值相同的子串，返回其在S中第pos个字符后(包含pos)第一次出现的位置
	//否则返回0，合法输入1<=pos<=StrLength(S)
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
	//用串V替换S中出现的所有与T相等且不重叠的子串
	if (!StrLength(T)) return ERROR;//若T为空，无从替换
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
		Concat(S, Z, Y);//这里不能用S,S,Y这种，concat会在第一步free(S)
		pos = i + v;
	}
	return OK;
}//Replace

Status StrInsert(HString& S, int pos, HString T) {
	//在串S的第pos个字符前插入串T
	//合法输入1<=pos<=StrLength(S)+1
	if (pos<1 || pos>StrLength(S) + 1) return ERROR;
	int s = StrLength(S);
	HString X, Y, Z;
	X.ch = Y.ch = Z.ch = NULL;
	X.length = Y.length = Z.length = 0;
	SubStr(X, S, 1, pos - 1);
	SubStr(Y, S, pos, s - pos + 1);//如果pos<s越界，SubStr返回ERROR，Y为空
	Concat(Z, X, T);
	Concat(S, Z, Y);
	return OK;
}//StrInsert

Status StrDelete(HString& S, int pos, int len) {
	//从串S中删除第pos个字符起长度为len的子串
	//合法输入1<=pos<=StrLength(S),0<=len<=StrLength(S)-pos+1
	if (pos<1 || pos>StrLength(S) || len<0 || len>StrLength(S) - pos + 1) return ERROR;
	int s = StrLength(S);
	HString X, Y;
	X.ch = Y.ch = NULL;
	X.length = Y.length = 0;
	SubStr(X, S, 1, pos - 1);
	SubStr(Y, S, pos + len, s - pos - len + 1);//如果pos+len>s越界，SubStr直接返回ERROR，Y为空
	Concat(S, X, Y);
	return OK;
}//StrDelete