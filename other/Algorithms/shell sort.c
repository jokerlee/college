#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define HZ 200

char fn[PATH_MAX];
int * data;


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
    int gap, i;
    for ( gap = n / 2; gap > 0; gap /= 2 )
    {
        for ( i = gap; i < n; ++i )
        {
            int tmp = a[i];
            int j = i;

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
    
    data = malloc( 100000000LL * sizeof(int) );

    FILE * fp = fopen( "in.dat", "r" );
    int i;
    //for ( i = 0; i < 1000000; ++i )
    //    fscanf( fp, "%d", &data[i] );
    
    double t = shell_sort( data, 100000000 );
    printf( "%f", t );

    free(data);
    return 0;
}






