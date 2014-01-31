/* BUPT OJ 1017 Herbert
 * 2010-06-02 11:37
 * 简单的搜索
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int dir[] = {-1, 0, 0, -1, 1, 0, 0, 1}; char map[25][25];
int search(int xx, int yy)
{
    int i, x, y;
    for (i=0; i<4; ++i)
    {
        x = xx+dir[2*i]; y = yy+dir[2*i+1];
        if (x<0 || x>23 || y<0 || y>24) continue;
        if (map[x][y]=='w' || map[x][y]=='*')
        {   map[x][y] = 't'; search(x, y);   }
    }
}
int main()
{
    int T, i, j; scanf("%d", &T);
    while (T--)
    {
        for (i=0; i<24; ++i) scanf("%s", map[i]);
        for (i=0; i<24; ++i) for (j=0; j<24; ++j)
            if (map[i][j] == 's') search(i, j);
        for (i=0; i<24; i++)
        {
            for (j=0; j<24; j++) if (map[i][j] == 'w') break;
            if (j!=24) break;
        }
        if (i!=24) puts("NO");
        else puts("YES");
    }
    return 0;
}
