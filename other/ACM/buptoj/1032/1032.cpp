/* BOJ 1032 和Pluto邻近的Vitamin部落
 * 2010-06-03 14:33
 * nlogn 的最长不降自序列
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#include <algorithm>
int b[50001], m[50001], n;
int lndss()
{
    int i, j, k, ans;
    for (i=0,ans=0,m[0]=0x3f3f3f3f; i<n; ++i) {
        j = std::upper_bound(m, m+ans+1, b[i])-m;
        if (j>ans) m[++ans] = b[i]; else if (b[i]<m[j]) m[j]=b[i]; }
    return ans+1;
}
int main()
{
    int T, i; scanf("%d", &T);
    while (T--)                 {
        scanf("%d", &n);
        for (i=0; i<n; ++i) scanf("%d", &b[i]);
        printf("%d\n", lndss()); }
    return 0;
}


