#include <stdio.h>
#define MAX 10000000

int x[MAX];

/* By Bob Sedgewick, scan from right to left */ 

void qsort1(int l, int u)
{
    if (l >= u) return;
    
    int i, m = u + 1, t = x[l];

    for (i = u; i >= l; --i)
    {
        if (x[i] >= t)
            swap(--m, i);
    }
    qsort(l, m-1);
    qsort(m+1, u);
}


void qsort(int l, int u)
{
    if (l >= u) return;

    int i = u + 1, 
        m = u + 1;
        t = x[l];
    do
    {
        while (x[--i] < t);
        swap(--m, i);
    }while (i != l);
    
    qsort(l, m-1);
    qsort(m+1, u);
}

int main()
{
    int n = 0;
    while (scanf("%d", &x[n++]) != EOF);
    qsort(0, n-1);
    return 0;
}
