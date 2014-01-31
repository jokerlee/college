/* BUPT OJ 1068 broj
 * 2010-06-01 12:34
 * 简单的递推
 * jokerleee@gmail.com
 * */

#include <stdio.h>
inline int len(long long n)
{ int l; for (l=0; n>0; n/=10,l++); return l; }
int main()
{
    long long n, s=0, l, b; scanf("%I64d", &n);
    for (b=1; b<=n; b*=10); b/=10;
    s += len(n)*(n-b+1);
    for (l=1,b=9; l<len(n); ++l,b*=10) s += b*l;
    printf("%I64d\n", s);
    return 0;
}
