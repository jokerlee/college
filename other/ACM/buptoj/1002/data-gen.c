#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int i, j, k, t;
    int r[3] = {1, 2, 3};
    srand(time(0));
    printf("3\n");
    for (i=0; i<3; ++i)
    {
        for (j=0; j<3; ++j)
            printf("%.2f ", (double)(rand()%1000000)/1000.0);
        putchar('\n');
    }
    for (i=0; i<2; ++i)
    {
        j = rand()%3;
        k = rand()%3;
        t = r[j];
        r[j] = r[k];
        r[k] = t;
    }
    for (i=0; i<3; ++i)
        printf("%d ", r[i]);
    printf("\n0\n");
    return 0;
}
