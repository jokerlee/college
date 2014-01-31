#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define HZ 200

char fn[PATH_MAX];
int * data = 0;


double get_uptime(void)
{
    unsigned long utime, stime;
    FILE * fp;

    if ((fp = fopen(fn, "r")) == NULL) {
		fprintf(stderr, "Cannot open %s:%s\n", fn, strerror(errno));
		exit(2);
    }
    
    fscanf( fp, "%*d %*s %*c %*d %*d %*d %*d %*d "
                "%*lu %*lu %*lu %*lu %*lu %lu %lu", &utime, &stime );
    fclose(fp);
    
    return (double)(utime + stime)/HZ;
}


void do_shell_sort( int a[], int n )
{
    long gap, i, tmp, j;
    for ( gap = n / 2; gap > 0; gap /= 2 )
    {
        for ( i = gap; i < n; ++i )
        {
            tmp = a[i];
            j = i;

            for ( ; j >= gap && tmp < a[ j - gap ]; j -= gap )
                a[ j ] = a[ j - gap ];
            a[ j ] = tmp;
        }
    }
}


long double shell_sort( int a[], int n )
{
    long double t = get_uptime();
    do_shell_sort( a, n );
    return get_uptime() - t;
}


int main( int argc, char * argv[] )
{
    int pid = getpid();
    sprintf( fn, "/proc/%d/stat", pid );
    
    data = malloc( 590000000L * sizeof(int) );
    setbuffer(stdout, NULL, 0);

    FILE * fp;
    fp = fopen("result.txt", "w");
    setbuffer(fp, NULL, 0);
    
    unsigned long i, j, n;
    double t[100][50];
    for ( i = 1<<17, n = 0; i <= (1<<27); i <<= 1, n++ )
    {
        printf("%d:", i);
        for ( j = 0; j < 20; ++j )
        {
            t[n][j] = shell_sort( data, i );
            
            if ( j != 0 ) printf("\b\b");
            printf( "%.2d", j );
            
            fprintf(fp, "%.3f ", t[n][j]);
        }
        putchar('\n');
        fputc('\n', fp);
    }
    free(data);

    return 0;
}






