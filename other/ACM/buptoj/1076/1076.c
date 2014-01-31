/* BUPT OJ 1076
 * 2010-06-01 3:54
 * 精度题，注意浮点转整数前要加eps
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#include <math.h>
int main()
{
    int x1, x2, y1, y2;
    double d, sq2 = sqrt(2.0);
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    while (x1 != -1)
    {
        d = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
        if (fabs(d/sq2 - (int)(d/sq2+0.001)) < 1e-6)
            printf("%d\n", (int)(pow(d/sq2,2)+0.001));
        else if (fabs(d - (int)(d+0.001)) < 1e-6)
            printf("%d\n", (int)(pow(d,2)+0.001));
        else
            puts("Impossible");
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    }
    return 0;
}
