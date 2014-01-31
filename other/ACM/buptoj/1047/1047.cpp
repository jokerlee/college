/* BUPT OJ 1047
 * 2010-06-01 3:32
 * 水题，用set水过。标准做法是先排序再去重
 * jokerleee@gmail.com
 * */

#include <cstdio>
#include <set>
using std::set;

int main()
{
    int n;
    set<int> s;
    while (scanf("%d", &n) != EOF)
        s.insert(n%42);
    printf("%d\n", s.size());
    return 0;
}
