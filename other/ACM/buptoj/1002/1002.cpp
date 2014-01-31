/* BUPT OJ 1002
 * 2010-05-31 
 * 逻辑简单，直接模拟；注意精度问题，用整数计算
 * jokerleee@gmail.com
 * */

#include <cstdio>

typedef struct
{
    int s[3];
    double max;
}S;

int main()
{
    static int f[8][3] = { {1,1,1}, {0,1,1}, {1,0,1}, {1,1,0},
                           {0,0,1}, {0,1,0}, {1,0,0}, {0,0,0} };
    int n, cnt = 1, rank[16384];
    S sc[16384];
    scanf("%d", &n);
    while (n)
    {
        double t;
        for (int i=0; i<n; ++i)
        {
            for (int j=0; j<3; ++j)
            {
                scanf("%lf", &t);
                sc[i].s[j] = int((t+0.001)*100);
            }   
        }
    
        for (int i=0; i<n; ++i) scanf("%d", &rank[i]);
        for (int i=0; i<n; ++i) rank[i]--;
        
        int k = rank[0];
        sc[k].max = sc[k].s[0] + sc[k].s[1] + sc[k].s[2];
        double sum = 0;
        for (int k=1,i; k<n; ++k)
        {
            i = rank[k];
            sc[i].max = -1;
            for (int j=0; j<8; ++j)
            {
                sum = sc[i].s[0]*f[j][0] + sc[i].s[1]*f[j][1] + sc[i].s[2]*f[j][2];
                if (sum > sc[i].max 
                    && (sum < sc[rank[k-1]].max
                        || sum == sc[rank[k-1]].max && rank[k] > rank[k-1]) )
                    sc[i].max = sum;
            }
            if (sc[i].max == -1)
            {
                sum = -1;
                break;
            }
        }
        if (sum == -1)
            printf("Case %d: No solution\n", cnt++);
        else
            printf("Case %d: %.2lf\n", cnt++, double(sc[rank[n-1]].max)/100.0);

        scanf("%d", &n);
    }
    return 0;
}
