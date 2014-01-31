/* BUPT OJ 1062 SKENER
 * 2010-06-02 14:56
 * 简单的模拟题
 * jokerleee@gmail.com
 * */
#include <stdio.h>
int main()
{   
    int r, c, zr, zc, i, j; char o[51][51];
    scanf("%d %d %d %d", &r, &c, &zr, &zc);
    for (i=0; i<r; ++i) scanf("%s", o[i]);
    for (i=0; i<r*zr; i++) 
    {
        for (j=0; j<c*zc; j++)
            putchar(o[i/zr][j/zc]);
        putchar('\n');
    }
    return 0;
}
