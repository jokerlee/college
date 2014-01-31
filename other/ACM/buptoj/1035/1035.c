/* BUPT OJ 1035 冥王星的故事III-和谈
 * 2010-06-02 11:09
 * 即求合法出栈序列数，Catalan数 c(2n,n)-c(2n,n+1)=1/(n+1)*c(2n,n)
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int C[] = {0, 2, 6, 20, 70, 252, 924, 3433, 12870, 48620, 184756}; // C(n,2n)
int main()
{
    int t, n; scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        printf("%d\n", C[n]/(n+1));
    }
    return 0;
}
