# include "visit.h"

Status MyPrint(int a) {
	//一个printf的visit函数
	if (!printf("%d ", a)) return ERROR;
	return OK;
}//MyPrint

Status MyPrint(char a) {
	//一个printf的visit函数
	if (!printf("%c ", a)) return ERROR;
	return OK;
}//MyPrint