/* BUPT OJ 1056
 * 2010-06-01 4:29
 * 简单的组合数学。n变形有n(n-3)/2条对角线，每两条对角线（四个定点）
 *     唯一确定一个交点，所以又C(n,4)个交点
 * jokerleee＠gmail.com
 * */

#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", n*(n-1)*(n-2)*(n-3)/24);
    return 0;
}
