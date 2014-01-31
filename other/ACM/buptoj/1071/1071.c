/* BUPT OJ 1071 奶牛健美队
 * 求逆序数，冒泡可过
 * 2010-06-02 13:59
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#define SWAP(a,b) t=a;a=b;b=t
int main()
{
    int i, j, n, t, c, s[300], b[300];
    scanf("%d", &n);
    for (i=0; i<n; ++i) scanf("%d %d", &b[i], &s[i]);
    for (i=0,c=0; i<n; ++i) for (j=i+1; j<n; ++j)
        if (b[j]<b[i] || b[j]==b[i] && s[j]<s[i])
        {    SWAP(s[i], s[j]); SWAP(b[i], b[j]); c++; }
    printf("%d\n", c); return 0;
}
