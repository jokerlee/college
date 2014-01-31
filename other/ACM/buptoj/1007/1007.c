/* BUPT OJ 1004 PKU 2282 (Shanghai 2004) the counting problem
 * 2010-06-03 4:29
 * 极其恶心的题目...
 * jokerleee@gmail.com
 * */

/* 注意处理0的问题
 * 第一位0的个数必须是0,
 * 第k位，对0~9每个数
 *   若 < 当前位:  (pre+1)*本位权
 *   若 = 当前位:  pre*本位权+post+1
 *   若 > 当前位:  pre*本位权
 * 最后一位
 *   0 或 <= : pre+1
 *   > :        pre
 * */


#include <stdio.h>
int cnt[10];
void swap(int * a, int * b){ int t=*a; *a=*b; *b=t; }
inline int pre(int d[], int k)
{ int i, r; for (i=0,r=0; i<k; ++i) r = r*10+d[i]; return r; }
inline int pst(int d[], int k, int n)
{ int r; for (++k,r=0; k<n; ++k) r = r*10+d[k]; return r; }
void count(int n)
{
    int i, b, k, d[9];
    if (n == 0) { cnt[0]++; return; }
    for (i=0,b=1; n>0; i++,n/=10,b*=10) d[i] = n%10;
    for (n=0; n<i/2; ++n) swap(&d[n], &d[i-n-1]);
    for (n=0,b/=10; n<i-1; ++n, b/=10) for (k=0; k<10; ++k)
        if (n == 0 && k == 0) continue;
        else if (k == 0 && d[n] != 0) cnt[0] += pre(d,n)*b;
        else if (k == 0 && d[n] == 0) cnt[0] += pre(d,n)*b - b + pst(d,n,i) + 1;
        else if (k  < d[n]) cnt[k] += pre(d,n)*b + b;
        else if (k == d[n]) cnt[k] += pre(d,n)*b + pst(d,n,i) + 1;
        else if (k  > d[n]) cnt[k] += pre(d,n)*b;
    for(n=0; n<10; ++n) 
        if (n > d[i-1]) cnt[n] += pre(d,i-1); 
        else cnt[n] += pre(d,i-1)+1;
        
}
int main()
{
    int i, x, y, d, l; char * c;
    while (scanf("%d %d,", &x, &y), x+y)
    {
        for (i=0; i<10; ++i) cnt[i] = 0;
        if (x < y) swap(&x, &y); count(y-1);
        for (i=0; i<10; ++i) cnt[i]=-cnt[i]; count(x);
        for (i=0,c=""; i<10; ++i,c=" ") printf("%s%d", c, cnt[i]);
        putchar('\n');
    }
    return 0;
}
