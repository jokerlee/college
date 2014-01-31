/* BUPT OJ 1064
 * 2010-6-1 01:11
 * 水题，简单的最大公约数
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int gcd(int a, int b)
{
    if (!b) return a;
    else return gcd(b, a%b);
}

int main()
{
    int n, nn[100], i, o;
    scanf("%d", &n);
    for (i=0; i<n; ++i)
        scanf("%d", &nn[i]);
    for (i=1; i<n; ++i)
    {
        o = gcd(nn[0]>nn[i]?nn[0]:nn[i], 
                nn[0]>nn[i]?nn[i]:nn[0]);
        printf("%d/%d\n", nn[0]/o, nn[i]/o);
    }
    return 0;
}
