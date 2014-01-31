/* BOJ1020, POJ2586 (Waterloo local 2000.01.29)
 * 2010-06-03 10:25
 * 贪心
 *   1. ssssdssssdss 4s-d>0
 *   2. sssddsssddss 3s-2d>0
 *   3. ssdddssdddss 2s-3d>0
 *   4. sddddsddddsd s-4d>0
 * jokerleee@gmail.com
 * */


#include <stdio.h>
int main()
{
    int s, d, i, max, sum, spls[] = {0, 3, 6, 8, 10};
    while (scanf("%d %d", &s, &d) != EOF) {
        max = -12 * d;
        for (i=4; i>0; --i) 
            if (i*s < (5-i)*d)    {
                sum = spls[i]*s - (12-spls[i])*d;
                max = sum; break; }
        if (max > 0) printf("%d\n", max);
        else puts("Deficit");             } 
    return 0;
}
