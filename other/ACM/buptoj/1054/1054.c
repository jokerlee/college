/* BUPT OJ 1054
 * 2010-06-01 4:20
 * 水题，类似简介排序
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#define SWAP(a,b) {t=n[a];n[a]=n[b];n[b]=t;}
int main()
{
    int n[3], t; char c[5];
    scanf("%d %d %d", &n[0], &n[1], &n[2]);
    scanf("%s", c); c[0] -= 'A'; c[1] -= 'A'; c[2] -= 'A';
    if (n[1] <= n[0]) SWAP(1,0)
    if (n[2] <= n[0]) SWAP(2,0)
    if (n[2] <= n[1]) SWAP(2,1)
    printf("%d %d %d\n", n[c[0]], n[c[1]], n[c[2]]);
    return 0;
}

