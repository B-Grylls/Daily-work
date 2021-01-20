#include <stdio.h>
#include <string.h>

void MyStrcpy_arr(char[], char[]);
void Mystrcpy_poi(char*, char*);
unsigned int MyStrlen_arr(char[]);
unsigned int MyStrlen_poi(char*);
void MyStrcat_arr(char[], char[]);
char* MyStrcat_poi(char*, char*);
int MyStrcmp_arr(char[], char[]);
int MyStrcmp_poi(char*, char*);

int main() {
	char str1[101], str2[101];
	char* pstr;
	printf("input string limited by 100:");
	gets_s(str2);
	gets_s(str1);
	//pstr = MyStrcat_poi(str1, str2);
	//printf("%s", pstr);
	//printf("%d", MyStrcmp_poi(str1,str2));//这里就不写switch选择机制，直接手动更换函数
	//puts(str1);
	return 0;
}

/*复制函数b到a*/
void MyStrcpy_arr(char a[], char b[]) {//arr=array 表示用字符数组做参数
	int i;
	for (i = 0; b[i] != '\0'; i++)
		a[i] = b[i];
	a[i] = '\0';
}

void Mystrcpy_poi(char* a, char* b) {//poi=pointer 表示用字符指针做参数
	while (*b != '\0') {
		*a = *b;
		b++;
		a++;
	}
	*a = '\0';
}

/*计算字符长度*/
unsigned int MyStrlen_arr(char a[]) {
	unsigned int len = 0;
	while (a[len] != '\0')
		len++;
	return len;
}

unsigned int MyStrlen_poi(char* a) {
	unsigned int len = 0;
	while (*a != '\0') {
		a++;
		len++;
	}
	return len;
}

/*连接函数，b到a*/
void MyStrcat_arr(char a[], char b[]) {
	int i = 0, j = 0;
	while (a[i] != '\0')
		i++;
	while (b[j] != '\0') {
		a[i] = b[j];
		i++;
		j++;
	}
	a[i] = '\0';
}

char* MyStrcat_poi(char* a, char* b) {
	char* p = a;
	while (*a != '\0')
		a++;
	while (*b != '\0') {
		*a = *b;
		a++;
		b++;
	}
	*a = '\0';
	return p;
}

/*比较函数，a-b*/
int MyStrcmp_arr(char a[], char b[]) {
	int i = 0;
	while (a[i] == b[i] && a[i] != '\0' && b[i] != '\0')
		i++;
	return a[i] - b[i];
}

int MyStrcmp_poi(char* a, char* b) {
	while (*a == *b && *a != '\0' && *b != '\0') {
		a++;
		b++;
	}
	return *a - *b;
}