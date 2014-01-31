#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define HZ 200

char fn[PATH_MAX];
int * data;

void swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
 
//对arr数组做从下标0到下标q的划分
int partition( int arr[], int p, int q )
{
    int low = p+1, high = q;
    int x = arr[p];
 
    while( low < high )
    {
        if( arr[low] <= x ) low++;
        else    swap( &arr[low], &arr[--high] );
    }
    swap( &arr[p], &arr[--low] );
    return low;
}

int part( int x[], int l, int u )
{
    if (l >= u) return;
    int i, m = l; /* m is the pivot */
    for (i = l+1; i <= u; ++i)
    {
        if (x[i] < x[l])
        {
            swap( &x[++m], &x[i] );
        }
    }
    int tmp = x[l]; x[l] = x[m]; x[m] = tmp;
    return m;
}

int rand_partition(int *arr,int p,int q)
{
    int rnd = p + rand()%(q-p);
    swap( &arr[p], &arr[rnd] );
    return partition( arr, p, q );
}
 
int do_get_kth_element( int arr[], int p, int q, int k )
{
    if ( p == q )    return arr[p];
    int pos = part( arr, p, q );
    int j = pos - p + 1;
 
    if ( k <= j )
        return do_get_kth_element( arr, p, pos, k );
    else
        return do_get_kth_element( arr, pos+1, q, k-j );
}

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


long double get_kth_element( int a[], int n, int k )
{
    long double t = get_uptime();
    do_get_kth_element( a, 0, n, k );
    return get_uptime() - t;
}


int main( int argc, char * argv[] )
{
    int pid = getpid();
    sprintf( fn, "/proc/%d/stat", pid );
    
    data = malloc( 100000000LL * sizeof(int) );

    int n = 100000;
    double t = get_kth_element( data, n, rand()%n );
    printf( "%f", t );

    free(data);
    return 0;
}
