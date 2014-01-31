/* BUPT OJ 1089
 * 2010-06-01 17:29
 * 公式题，递推也能做 1^2*(n-1)+...+(n-i+1)^2*(i-1)+...+(n-1)^2*1
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int main()
{
    int n, s, i;
    scanf("%d", &n);
    while (n)
    {
        for (i=2,s=0; i<=n; ++i) s += (n-i+1)*(n-i+1)*(i-1);
        printf("%d\n", s);
        scanf("%d", &n);
    }
    return 0;
}
