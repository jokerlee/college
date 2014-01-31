#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000000


/* generate a random integers int in [m, n] */

#if RAND_MAX < MAX

int randint(int m, int n)
{
    int r = (rand()<<15) + rand();
    return r%(n - m + 1) + m;
}

#else

int randint(int m, int n)
{
    return rand()%(n - m + 1) + m;
}
#endif


int main(int argc, char * argv[])
{
    int i, n = 10000000;
    if (argc > 1) n = atoi(argv[1]);
    FILE * ofp = fopen("in.dat", "w");

    srand(time(0));
    for (i = 0; i < n; ++i)
        fprintf(ofp, "%d\n", randint(0, MAX));
    fclose(ofp);

    return 0;
}
