/* BUPT OJ 1059
 * 2010-06-01 16:41
 * 一个组合生成问题，因为是固定的C(9,7)，转成C(9,2)直接循环解决
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int main()
{
    int i, j, k, a[9], f, p, q, n=9;
    for (i=0; i<9; ++i) 
    { 
        scanf("%d", &a[i]);
        if (a[i] < 1 || a[i] > 99) i--;
    }
    for (i=0,k=0; i<n; ++i) k += a[i];
    for (i=0, f=0; i<n; ++i) 
    {
        for (j=i+1; j<n; ++j) if (k-a[i]-a[j]==100) f++, p=i, q=j;
        if (f>1) break;
    }
    if (f==0 || f>1) puts("Impossible");
    else for (i=0; i<n; ++i) if (i!=p && i!=q) printf("%d\n", a[i]);
    return 0;
}
