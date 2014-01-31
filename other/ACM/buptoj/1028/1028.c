/* BUPT OJ 1028
 * 水题，先排序再贪心
 * 2010-6-1 00:09 1A
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#include <stdlib.h>

int cmp(const void * a, const void * b)
{
    return *(int *)b - *(int *)a;
}

int main()
{
    int m, n, i, j, big[10000], sml[10000], cnt = 0;
    scanf("%d %d", &n, &m);
    for (i=0; i<n; ++i)
        scanf("%d", &big[i]);
    for (i=0; i<m; ++i)
        scanf("%d", &sml[i]);
    
    qsort(big, n, sizeof(int), cmp);
    qsort(sml, m, sizeof(int), cmp);

    for (i=0,j=0,cnt=n; i<n && j<m; ++i, ++j)
    {
        while (sml[j] >= big[i] && j < m) j++;
        if (j != m) cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}
