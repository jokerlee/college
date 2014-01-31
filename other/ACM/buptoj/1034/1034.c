/* BOJ 1034 冥王星的故事II-占领岛国
 * 2010-06-03 23:05
 * 简单的floyd算法
 * jokerleee@gmail.com
 */



#include <stdio.h>
#include <string.h>
#define M 0x3f3f3f3f
int main()
{
    int p[101][101], m, n, i, j, k;
    scanf("%d%d", &n, &m); memset(p, 0x3f, sizeof(p));
    while (m--){ scanf("%d%d%d", &k, &i, &j); p[j][i]=p[i][j]=(k==0?1:M);}
    for (k=1; k<=n; ++k) for (i=1; i<=n; ++i) for (j=1; j<=n; ++j)
        if (p[i][j]>p[i][k]+p[k][j])  p[i][j] = p[i][k] + p[k][j];
    scanf("%d", &m); while(m--) scanf("%d%d", &i, &j), printf("%s\n", p[i][j]<10000?"yes":"no");
    return 0;
}

