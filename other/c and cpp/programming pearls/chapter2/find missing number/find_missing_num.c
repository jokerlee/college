#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int UINT;

UINT ans = 0;

int main()
{
    find(32, 0);
    printf("%d\n", ans);
    return 0;
}

void get_filename(int n, char * name, int i)
{
    if (n >= 10) strcat(name, n/10+'0');
    strcat(name, n%10+'0');
    strcat(name, '0'+i);
    strcat(name, ".dat");
}

void search(int bit, int head)
{
    FILE * ifp, ifp0, ifp1;
    UINT mask = 1 << (bit-1);
    UINT num, cnt0 = 0, cnt1 = 0;
    char fn[10] = {0},
         fn0[10] = {0},
         fn1[10] = {0};
    
    if (bit == 0) return;
    
    get_filename(bit, fn);
    get_filename(bit-1, fn0, 0);
    get_filename(bit-1, fn1, 1);
    ifp = fopen(fn, "r");
    ifp1 = fopen(fn0, "w");
    ifp0 = fopen(fn1, "w");

    while (fscanf(ifp, "%d", &num) != EOF)
    {
        if (num & mask)
        {
            fprintf(fn1, "%d\n", tmp);
            cnt1 ++;
        }
        else 
        {
            fprintf(fn0, "%d\n", tmp);
            cnt0 ++;
        }
    }
    if (cnt0 < (0 << bit-1))
    {
        if (cnt0) search(bit-1, 0);
        ans = (ans << 1) + 0;
    }
    else
    {
        if (cnt1) search(bit-1, 1);
        ans = (ans << 1) + 1;
    }
}


