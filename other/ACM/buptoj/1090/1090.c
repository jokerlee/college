/* BUPT OJ 1090
 * 2010-06-01 1:45
 * 第k大数quick-select算法
 * jokerleee@gmail.com
 * */

#include <stdio.h>

int select(int a[], int l, int r, int k)
{
    if (l==r) return a[l];
    int x = a[l+rand()%(r-l+1)], i = l-1, j = r+1, t;
    while (i<j)
    {
        while (a[++i] < x); while (a[--j] > x);
        if (i<j) { t = a[i]; a[i] = a[j]; a[j] = t; }
    }
    if (j==r) j--;
    i = j-l+1;
    if (k<=i) return select(a, l, j, k);
    else return select(a, j+1, r, k-i);
}

int main()
{
    int n, i, num[201];
    scanf("%d", &n);
    for (i=0; i<2*n+1; ++i)
        scanf("%d", &num[i]);
    printf("%d\n", select(num, 0, 2*n, n+1));
    return 0;
}
