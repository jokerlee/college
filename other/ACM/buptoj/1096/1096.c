/* BUPT OJ 1096
 * 2010-06-01 11:02
 * 一道简单的图论题，判断图是否是一条线；一条线的特征是：有一个点出度为1
 *     入读为0，还有一个点出度为0入读为1，其他线上的点出入度都为1。还需要
 *     一个搜索判断整条直线是否连通。
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#include <string.h>
int main()
{
    int n, i, a, b, s, in[1000]={0}, out[1000]={0}, map[1000];
    scanf("%d", &n);
    memset(map, 0xff, sizeof(int)*1000);
    for (i=0; i<n-1; ++i)
    {
        scanf("%d %d", &a, &b);
        in[b]++;out[a]++;map[a]=b;
    }
    for (i=a=b=0; i<n; ++i)
        if (in[i]==1 && out[i]==0) a++;
        else if (in[i]==0 && out[i]==1) b++, s=i;
        else if (in[i]!=1 || out[i]!=1 || a>1 || b>1) break;
    if (i==n)
    {
        for (i=s,a=0; map[i]>=0; i=map[i],a++);
        if (a==n-1) puts("Yes");
        else puts("No");
    }
    else puts("No");
    return 0;
}
