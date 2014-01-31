/* BUPT OJ 1060 NPUZZLE
 * 2010-06-02 20:13
 * 简单的模拟题
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int main()
{
    char p[4][5]; int i, j, d;
    for (i=0; i<4; ++i) scanf("%s", p[i]);
    for (i=0,d=0; i<4; ++i)
        for (j=0; j<4; ++j) if (p[i][j] != '.')
            d += abs((p[i][j]-'A')/4-i) + abs((p[i][j]-'A')%4-j);
    printf("%d\n", d);
    return 0;
}
