/* BUPT OJ 1016 network
 * 2010-06-02 21:11
 * 基础的最小生成树，kruskal算法
 * jokerleee@gmail.com
 * */


#include <cstdio>
#include <algorithm>
#define N 1000005
int id[N], eu[N], ev[N], ew[N], n, m, pnt[1001], map[1001][1001];
int cmp(const int & i, const int & j){return ew[i]<ew[j];}
int find(int x){if (x!=pnt[x]) pnt[x]=find(pnt[x]); return pnt[x];}
int kruskal()
{
    int ret=0, i, j, p;
    for (i=0; i<n; ++i) pnt[i] = i;
    for (i=0; i<m; ++i) id[i] = i;
    std::sort(id, id+m, cmp);
    for (j=-1,i=1; i<n; ++i){
        while (p=id[++j], find(eu[p])==find(ev[p]));
        ret+=ew[p]; pnt[find(ev[p])]=find(eu[p]);
    }
    return ret;
}

int main()
{
    int i, j; 
    while (scanf("%d", &n) != EOF ) {
        for (i=0; i<n; ++i) for (j=0; j<n; ++j) scanf("%d", &map[i][j]);
        for (i=m=0; i<n; ++i) for (j=i+1; j<n; ++j) 
            if (map[i][j]) {eu[m] = i; ev[m] = j; ew[m++] = map[i][j];}
        printf("%d\n", kruskal()); 
    }return 0;
}
