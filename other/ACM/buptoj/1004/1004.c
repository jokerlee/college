/* BUPT OJ 1004
 * jokerleee@gmail.com
 * 2010-5-31
 * DP最长上升子序列，正着求一次，反着求一次，得到每一个位置上的最长上升子序
 * 列（必须包括该位），然后枚举每一位找正反最长上升子序列长度之和最长的位置
 * */

#include <stdio.h>

void reverse(int num[], int n)
{
    int i, t;
    for (i=0; i<n/2; ++i) //  reverse the array
    {
        t = num[i];
        num[i] = num[n-i-1];
        num[n-i-1] = t;
    }
}

int dp(int num[], int max[], int n)
{
    int i, j;
    max[0] = 1;
    for (i=1; i<n; ++i)
    {
        max[i] = 1; // 子序列长度至少是1位，即只有自己
        for (j=0; j<i; ++j)
            if ( num[i] > num[j] )
                max[i] = max[j] + 1 > max[i] ? max[j] + 1 : max[i];
    }
}

int main()
{
    int n, i, num[51], max[51], rmax[51], min;
    
    while (scanf("%d", &n) != EOF)
    {
        for (i=0; i<n; ++i)
            scanf("%d", &num[i]);
    
        dp(num, max, n); // max increase sub-sequence

        reverse(num, n);
        dp(num, rmax, n);
        reverse(rmax, n);
    
        for (i=0, min=n-1; i<n; ++i)
            if (n - max[i] - rmax[i] + 1 < min)
                min = n - max[i] - rmax[i] + 1;
        printf("%d\n", min);
    }
    return 0;
}
