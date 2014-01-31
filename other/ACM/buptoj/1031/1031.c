/* BUPT OJ 1031
 * 2010-06-01 00:32
 * 判断一个数是不是完全平方数
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#include <math.h>

// 1+3+5+7+…+(2n-1)=n^2 
int judge(int n) // 9ms
{
    int i;
    for (i=1; n>0; i+=2) n-=i;
        return n == 0;
}


/*
int judge(int n) // 7ms
{
    int a = (sqrt(n)+0.5);
    return a * a == n;
}
*/

int main()
{
    int n;
    scanf("%d", &n);
    printf("%s\n", acc(n) && judge(n) ? "Yes" : "No");
    return 0;
}
