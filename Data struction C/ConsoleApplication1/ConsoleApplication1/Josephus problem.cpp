#include <stdio.h>

/*约瑟夫环问题，目前写一个实际的问题，对于递归子环的构造后面需要时候补充
  特工和99个人围成一圈，从一到五报数，报数到5就自杀，依次循环，特工最后一个自杀所以活了下来，问特工在第几位*/
const int N = 100;
int main() {//构造一个数组，利用筛法和计数，最后输出position,该方法模拟了全过程，在N极大情况下效率低
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