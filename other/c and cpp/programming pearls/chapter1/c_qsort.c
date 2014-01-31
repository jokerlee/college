#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int intcomp(int * x, int * y)
{
    return *x - *y;
}

int a[1000000];
int main()
{
    int i = 0,
        n = 0;
    FILE * ifp,
         * ofp;
    time_t start,
           finish;
    double total;

    start = clock();

    ifp = fopen("in.dat", "r");
    while (fscanf(ifp, "%d", &a[n]) != EOF)
        n++;
    fclose(ifp);

    qsort(a, n, sizeof(int), intcomp);

    ofp = fopen("out3.dat", "w");
    for (i=0; i<n; ++i)
        fprintf(ofp, "%d\n", a[i]);
    fclose(ofp);

    finish = clock();
    total = (double)(finish - start)/(CLOCKS_PER_SEC);
    printf("%f\n", total);

    return 0;
}
