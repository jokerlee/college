/* BUPT OJ 1078
 * 2010-06-01 2:23
 * 打表题，先用搜索计算答案
 * jokerleee@gmail.com
 * */
#include <stdio.h>

int ans[] = { 1,2,5,14,42,132,429,1430,4862,16796,58786,208012,
    742900,2674440,9694845,35357670,129644790,477638700,1767263190 };
/*
int calc(int r, int nb, int ns)
{
    if (nb == 0) return 1;
    if (ns == 0) return 1;
    int s = calc(r+1, nb, ns-1);
    if (r>0) s += calc(r-1, nb-1, ns);
    return s;
}

void make_table()
{
    int i;
    for (i=2; i<40; i+=2)
        printf("%d,", calc(0, i/2, i/2));
}
*/
int main()
{
    int t, n;
    //make_table();
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        printf("%d\n", ans[(n-2)/2]);
    }
    return 0;
}
