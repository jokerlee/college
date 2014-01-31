/* BUPT OJ 1003 
 * 2010-06-31
 * 快速查找，STL map和set系数太大，会TLE；用hash_set可以过；快排+二分也可以
 * jokerleee@gmail.com
 * */

// WA when use char *, string AC

#include <cstdio>
#include <string.h>
#include <ext/hash_set>

using namespace std;
using namespace __gnu_cxx;

struct shash
{
    size_t operator()(const string & s)const
    {
        return __stl_hash_string(s.c_str());
    }
};
hash_set<string, shash> hs;
int main()
{
    int n;
    char buf[11];
    while (scanf("%d", &n) != EOF)
    {
        hs.clear();
        while (n--)
        {
            scanf("%s", &buf);
            hs.insert(buf);
        }
        scanf("%d", &n);
        while (n--)
        {
            scanf("%s", &buf);
            if (hs.find(buf) != hs.end())
                puts("YES");
            else
                puts("NO");
        }
    }
    return 0;
}
