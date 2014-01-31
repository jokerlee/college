/* BUPT OJ 1092
 * 2010-06-01 12:28
 * 搜索，需要记忆化，否则TLE
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#include <string.h>
int ans[51][51] = {0};
int search(int k, int r, int n)
{
    if (ans[k][r] >= 0) return ans[k][r];
    if (k+2*(r-1) > n) return 0;
    if (r == 1) return n-k+1;
    ans[k][r] = 0;
    ans[k][r] += search(k+2, r-1, n);
    ans[k][r] += search(k+1, r, n);
    return ans[k][r];
}
int main()
{
    int n, k, i;
    scanf("%d %d", &n, &k);
    while (n && k)
    {
        memset(ans, 0xff, sizeof(ans));
        if (k==1) printf("%d\n", n);
        else printf("%d\n", search(1,k,n));
        scanf("%d %d", &n, &k);
    }
    return 0;
}
