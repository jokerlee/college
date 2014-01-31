/* BUPT OJ 1024 Best SMS to Type
 * 2010-6-2 2:09
 * 简单的模拟题，注意空格没有fix time，所以两个连续的空格不处理
 * jokerleee@gmail.com
 */

#include <stdio.h>
#define POS(c) (key[c-'A']/10)
#define CNT(c) (c==' '?1:key[c-'A']%10)
char key[] = {21,22,23,31,32,33,41,42,43,51,52,53,
    61,62,63,71,72,73,74,81,82,83,91,92,93,94};
int main()
{
    int t, p, w, l, i, s; char bf[1001];
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &p, &w); getchar(); gets(bf);
        for (l=0; bf[l]; ++l);
        for (i=1, s=CNT(bf[0])*p; i<l; ++i)
        {
            if (bf[i]!=' ' && POS(bf[i])==POS(bf[i-1])) s += w;
            s += p*CNT(bf[i]);
        }
        printf("%d\n", s);
    }
    return 0;
}
