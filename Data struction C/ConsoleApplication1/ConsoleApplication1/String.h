#pragma once
# include <stdio.h>
# include <stdlib.h>
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0
# define MAXSTRLEN 255//˳��洢��һ���Ĵ�С
# define CHUNKSIZE 80//�����Ĵ�С

typedef int Status;

typedef unsigned char SString[MAXSTRLEN + 1];//���Ķ���˳��洢��0�ŵ�Ԫ��Ŵ��ĳ���

typedef struct {//���Ķѷ���洢������Ŀռ�ʱ�����Ŵ��ĳ��ȱ仯���仯
	char* ch;//������ʼָ��
	int length;//����
}HString;

typedef struct Chunk {//������һ�����
	char ch[CHUNKSIZE];//һ������ܴ洢���ַ�
	Chunk* next;
}Chunk;
typedef struct {//������������ʱֻ�����ṹ����
	Chunk* head, * tail;//����ͷβָ�룬��ͷ���
	int curlen;//���ĳ���
}LString;

Status StrAssign(SString& S, const char* chars);
Status StrAssign(HString& S, const char* chars);
int StrCompare(SString S, SString T);
int StrCompare(HString S, HString T);
int StrLength(SString S);
int StrLength(HString S);
Status Concat(SString& T, SString S1, SString S2);
Status Concat(HString& T, HString S1, HString S2);
Status SubStr(SString& Sub, SString S, int pos, int len);
Status SubStr(HString& Sub, HString S, int pos, int len);
Status ClearStr(SString& S);
Status ClearStr(HString& S);
Status StrCopy(SString& T, SString S);
Status StrEmpty(SString S);

int Index(SString S, SString T, int pos);
int Index(HString S, HString T, int pos);
Status Replace(SString& S, SString T, SString V);
Status Replace(HString& S, HString T, HString V);
Status StrInsert(SString& S, int pos, SString T);
Status StrInsert(HString& S, int pos, HString T);
Status StrDelete(SString& S, int pos, int len);
Status StrDelete(HString& S, int pos, int len);
