/* BUPT OJ 1073 数羊
 * 2010-06-02 13:46
 * 水题....不能更水了
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int main()
{
    int n, c=0, t; scanf("%d", &n);
    while(n--) {scanf("%d", &t); if (t==0) c++; else if (t==1) c--;}
    printf("%d\n", c); return 0;
}
