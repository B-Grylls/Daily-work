#include <stdio.h>

/*Լɪ�����⣬Ŀǰдһ��ʵ�ʵ����⣬���ڵݹ��ӻ��Ĺ��������Ҫʱ�򲹳�
  �ع���99����Χ��һȦ����һ���屨����������5����ɱ������ѭ�����ع����һ����ɱ���Ի������������ع��ڵڼ�λ*/
const int N = 100;
int main() {//����һ�����飬����ɸ���ͼ�����������position,�÷���ģ����ȫ���̣���N���������Ч�ʵ�
    int circle[N];
    int i,death=0,pos=0,count=0;
    for (i = 0; i < N; i++)
        circle[i] = 1;
    do {
        pos++;
        if (pos >= N)
            pos = 0;
        if (circle[pos])
            count++;
        if (count == 5) {
            circle[pos] = 0;
            count = 0;
            death++;
        }
    } while (death != N);
    printf("the survival position is:%d\n", pos);
    return 0;
}