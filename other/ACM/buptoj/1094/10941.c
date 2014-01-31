/* BUPT OJ 1094 ACM的组队
 * 2010-06-01 21:58
 * 先排序，相邻做差，从这些差里DP出k个和最小的且互相不相邻的数。
 * 前i个数中j个不相邻数的最小和：dp(i,j) = min(dp(i-2,j-1)+n[i],dp(i-1,j))
 * jokerleee@gmail.com
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(a,b) (a)<(b)?(a):(b)
int x[2000], dp[2000][700];
int cmp(const void * a, const void * b)
{ return *(int*)a - *(int *)b; }
int main()
{
    int n, k, i, j, t;
    scanf("%d %d", &n, &k);
    for (i=0; i<n; ++i) scanf("%d", &x[i]);
    qsort(x, n, sizeof(int), cmp);
    for (i=0; i<n-1; ++i) 
        x[i] = (x[i+1]-x[i])*(x[i+1]-x[i]);
    memset(dp, 0x7f, sizeof(dp));
    memset(dp[0], 0x00, sizeof(dp[0]));
    for (i=0; i<n; ++i) dp[i][0] = 0;
    dp[1][1] = x[0];
    for (i=2; i<n; ++i)
        for (j=1; j<=(i+1)/2; ++j)
            dp[i][j] = MIN(dp[i-2][j-1]+x[i-1], dp[i-1][j]);
    printf("%d\n", dp[n-1][k]);
    return 0;
}

