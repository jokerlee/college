/* BUPT OJ 1033
 * 2010-06-01 3:25
 * 水题...
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int main()
{
    int n,  m, a[1000], i, sum;
    double r, avg;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &m);
        for (i=0; i<m; ++i) scanf("%d", &a[i]);
        for (i=0,avg=0; i<m; ++i) avg += a[i];
        avg = avg/m;
        for (i=0,sum=0; i<m; ++i) if (a[i] > avg) sum++;
        printf("%.3f%\n", 100.0*(double)sum/m);
    }
    return 0;
}

