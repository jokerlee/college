/* BUPT OJ 1048 HERMAN
 * 2010-06-02 1:15
 * 水题，注意pi的精度得够大..
 * jokerleee@gmail.com
 * */

#include <stdio.h>
double pi = 3.14159265358979323846264338327950;
int main()
{
    int n; scanf("%d", &n);
    printf("%.6f\n", pi*n*n);
    printf("%d.000000\n", 2*n*n);
    return 0;
}
