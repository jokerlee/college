/****************************************************************
 * Problem description: 
 * Input:
 * A file containing at most n positive integers, each less
 * than n, where n = 107. It is a fatal error if any integer
 * occurs twice in the input. No other data is associated
 * with the integer.
 * Output:
 * A sorted list in increasing order of the input integers.
 * Constraints:
 * At most (roughly) 1M of storage is available in main memory;
 * ample disk storage is available. The run time can be at most
 * several minutes; a run time of ten seconds need not be decreased.
 ******************************************************************/


#include <stdio.h>
#include <time.h>
#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define MAX 10000000

int bits[1 + MAX/BITSPERWORD];

void set(int i)
{
    bits[i>>SHIFT] |= (1<<(i & MAX));
}

void clr(int i)
{
    bits[i>>SHIFT] &= (1<<(i & MAX));
}

int test(int i)
{
    return bits[i>>SHIFT] & (1<<(i & MAX));
}

int main()
{
    int i;
    time_t start, finish;
    double total;
    FILE * ifp,
         * ofp;
    
    start = clock();
    ifp = fopen("in.dat", "r");
    while (fscanf(ifp, "%d", &i) != EOF)
        set(i);
    fclose(ifp);

    ofp = fopen("out1.dat", "w");
    for (i=0; i<MAX; ++i)
        if (test(i))
            fprintf(ofp, "%d\n", i);
    fclose(ofp);

    finish = clock();
    total = (double)(finish - start)/(CLOCKS_PER_SEC);
    printf("%f\n", total);

    return 0;
}
