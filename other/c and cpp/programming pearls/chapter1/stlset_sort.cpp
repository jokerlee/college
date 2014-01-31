#include <cstdio>
#include <ctime>
#include <iostream>
#include <set>
#define N 1000000

using namespace std;

int main()
{
    time_t start, finish;
    
    start = clock();
    
    set<int> a;
    FILE * ifp = fopen("in.dat", "r");
    int tmp;
    while (fscanf(ifp, "%d", &tmp) != EOF)
        a.insert(tmp);
    fclose(ifp);

    FILE * ofp = fopen("out2.dat", "w");
    set<int>::iterator i = a.begin();
    for ( ; i!=a.end(); ++i)
        fprintf(ofp, "%d\n", *i);
    fclose(ofp);

    finish = clock();
    double total = (double)(finish - start)/(CLOCKS_PER_SEC);
    printf("%f\n", total);

    return 0;
}
