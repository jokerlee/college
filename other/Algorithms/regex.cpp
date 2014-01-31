#include <cstring>
#include <iostream>

using namespace std;

bool is_match(const char * s, const char * t)
{
    while (*s && *t)
    {
        if (*t != '*' && *s == *t)
            ++s, ++t;
        else if (*t != '*' && *s != *t)
            return false;
        else if (*t == '*')
        {
            do ++t; while (*t == '*');
            if (*t == 0) return true;
            for ( ; *s; ++s)
                if (*s == *t && is_match(s+1, t+1))
                    return true;
            return false;
        }
    }
    while (*t == '*') ++t;
    if (*s == *t) return true;
    else return false;
}

int main(int argc, char * argv[])
{
    if (is_match(argv[1], argv[2]))
        cout << "match" << endl;
    else cout << "not match" << endl;
    return 0;
}
