# include "visit.h"

Status MyPrint(int a) {
	//һ��printf��visit����
	if (!printf("%d ", a)) return ERROR;
	return OK;
}//MyPrint

Status MyPrint(char a) {
	//һ��printf��visit����
	if (!printf("%c ", a)) return ERROR;
	return OK;
}//MyPrint