#include <stdio.h>
#define MAX 10000000

int x[MAX];

void qsort(int l, int u)
{
    if (l >= u) return;
    
    int t = x[i], i = l, j = u + 1;
    
    while (1)
    {
        do i++; while (i <= u && x[i] < t);
        do j++; while (x[j] > t);
        if (i > j) break;
        swap(i, j);
    }
    swap(l, j);
    qsort(l, j-1);
    qsort(j+1, u);
}

int main()
{
    int n = 0;
    while (scanf("%d", &x[n++]) != EOF);
    qsort(0, n-1);
    return 0;
}
