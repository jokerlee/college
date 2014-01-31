/* BUPT OJ 1099
 * 2010-06-01 11:33
 * 水题，标记数组暴力可过，
 * jokerleee@gmail.com
 * */

#include <stdio.h>

int main()
{
    int L, N, i, x, d, k, f[500001] = {0};
    scanf("%d %d", &L, &N);
    while (N--)
    {
        scanf("%d %d %d", &x, &d, &k);
        for (i=x; i<x+d*k; i+=d) f[i]++;
    }
    for (i=0,x=0; f[i]==0; ++i); if (f[i]>1) x=1;
    for (d=500000,k=i; i<=L && !x; i=k)
    {
        do ++k; while (f[k] == 0 && k<=L);
        if (k == L+1) break;
        if (f[k]>1) x=1;
        else if (k-i<d) d = k-i;
    }
    if (x==1) puts("0");
    else printf("%d\n", d);
    return 0;
}
