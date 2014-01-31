/* BUPT OJ 1093 
 * 2010-06-01 1:24
 * DP最长上升子序列
 * jokerleee@gmail.com
 * */

#include <stdio.h>

int max[300];
int mis(int num[], int n)
{
    int i, j;
    max[0] = 1;
    for (i=1; i<n; ++i) 
    {
        max[i] = 1;
        for (j=0; j<i; ++j)
            if (num[i]>num[j] && max[j]+1>max[i])
                max[i] = max[j]+1;
    }
    for (i=j=0; i<n; ++i)
        if (max[i] > j) j = max[i];
    return j;
}

int main()
{
    int T, n, num[300], i;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (i=0; i<n; ++i)
            scanf("%d", &num[i]);
        printf("%d\n", mis(num, n));
    }
    return 0;
}
