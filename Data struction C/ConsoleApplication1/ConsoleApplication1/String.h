#pragma once
# include <stdio.h>
# include <stdlib.h>
# define OVERFLOW -2
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0
# define MAXSTRLEN 255//顺序存储串一个的大小
# define CHUNKSIZE 80//块链的大小

typedef int Status;

typedef unsigned char SString[MAXSTRLEN + 1];//串的定长顺序存储，0号单元存放串的长度

typedef struct {//串的堆分配存储，分配的空间时刻随着串的长度变化而变化
	char* ch;//串的起始指针
	int length;//串长
}HString;

typedef struct Chunk {//块链的一个结点
	char ch[CHUNKSIZE];//一个结点能存储的字符
	Chunk* next;
}Chunk;
typedef struct {//块链，不灵活，暂时只给出结构定义
	Chunk* head, * tail;//串的头尾指针，有头结点
	int curlen;//串的长度
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
