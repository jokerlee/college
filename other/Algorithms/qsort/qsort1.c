#include <stdio.h>
#define MAX 20000000


int x[MAX];

void qsort(int l, int u)
{
    if (l >= u) return;
    int i, m = l; /* m is the pivot */
    for (i = l+1; i <= u; ++i)
    {
        /* invariant: x[l+1~m]   <  x[l] &&
                      x[m+1~i+1] >= x[l] */
        if (x[i] < x[l])
        {
            int tmp = x[++m];
            x[m] = x[i];
            x[i] = tmp;
        }
    }
    int tmp = x[l]; x[l] = x[m]; x[m] = tmp;
    /* x[l~m-1] < x[m] <= x[m+1~u] */
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
