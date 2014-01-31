/* BUPT OJ 1022 Steps
 * 2010-06-01 00:49
 * 当步长先增后降是，取得最小步数，余下的距离用最大步数补齐
 * 1 + 2 +...+ n-1 + n + n-1 +...+ 2 + 1 = n^2
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#include <math.h>

int main()
{
    int n, x, y, s, b;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d %d", &x, &y); s=0;
        if (x != y)
        {
            x = y - x; b = (int)(sqrt(x)+0.001);
            x = x-b*b; s = 2*b-1;
            while (x) if (x>=b) s++,x-=b; else b--;
        }
        printf("%d\n", s);
    }
    return 0;
}
