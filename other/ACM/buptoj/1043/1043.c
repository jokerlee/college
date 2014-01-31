/* BUPT OJ 1043
 * 2010-06-01 3:01
 * 简单的线段树，只有插入操作
 * jokerleee@gmail.com
 * */

#include <stdio.h>

struct node
{
    int r, l, c;
    int s, e, m, len;
}tree[1<<19];

void build(int s, int e, int d)
{
    tree[d].s = s; tree[d].e = e; tree[d].m = (s+e)/2;
    if (s+1 == e) return;
    build(s, (s+e)/2, d*2+1);
    build((s+e)/2, e, d*2+2);
}

void init()
{
    int i;
    for (i=0; i<(1<<18); ++i)
        tree[i].r = tree[i].l = tree[i].c = tree[i].len = 0;
}

int insert(int s, int e, int d)
{
    if (tree[d].s >= s && tree[d].e <=e ) tree[d].c++;
    else
    {
        if (tree[d].m > s) tree[d].l = insert(s, e, d*2+1);
        if (tree[d].m < e) tree[d].r = insert(s, e, d*2+2);
    }
    if (tree[d].c) tree[d].len = tree[d].e - tree[d].s;
    else tree[d].len = tree[d].l + tree[d].r;
    return tree[d].len;
}

int main()
{
    int l, r;
    init(); 
    build(0, (1<<18)-1, 0);
    while (scanf("%d %d", &l, &r) != EOF)
        insert(l, r, 0);
    printf("%d\n", tree[0].len);
}
