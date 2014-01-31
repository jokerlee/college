/* BUPT OJ 1023 Ancient Keyboard
 * 2010-06-02 21:49
 * 简单的模拟题，注意在一个时间点上可能有多个键的状态发生变化
 * jokerleee@gmail.com
 * */


#include <stdio.h>
#include <string.h>
int a[1001][1001], len[1001];
int main()
{
    int t, n, p, q; char s[3]; scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        memset(a, 0, sizeof(a)); memset(len, 0, sizeof(len));
        while (n--) { 
            scanf("%s %d %d", s, &p, &q); 
            a[p][len[p]]=s[0]; len[p]++; a[q][len[q]]=-s[0]; len[q]++;
        };
        for (n=p=0; n<1001; ++n) {
            for (q=0; q<len[n]; ++q) if (a[n][q]>0) p++; else if (a[n][q]<0) p--;
            if (p>0) putchar(p+'A'-1);
        } putchar('\n');
    } return 0;
}
