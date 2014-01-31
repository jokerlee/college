/* BUPT OJ 1051
 * 2010-06-01 4:05
 * 水题
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#include <math.h>
int main()
{
    int n, w, h, len;
    scanf("%d %d %d", &n, &w, &h);
    double max = sqrt(w*w+h*h);
    while (n--)
    {
        scanf("%d", &len);
        if (len<=max) puts("DA");
        else puts("NE");
    }
    return 0;
}
