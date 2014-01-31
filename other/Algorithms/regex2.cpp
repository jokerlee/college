#include <iostream>
#include <cstring>

using namespace std;

const int MAX_LEN = 1024;
 
int dp[MAX_LEN][MAX_LEN];
 
bool is_match(int p, int q, const char * s, const char * t)
{
    if (dp[p][q] >= 0) return dp[p][q];
 
    int &ans = dp[p][q] = 0;
 
    if (s[p] && t[q]) {
        ans = 1;
    } else if (!s[p] || !t[q]) {
        if (t[q] == '*') {
            ans = is_match(p, q + 1, s, t);
        }
    } else {
        if (t[q] == '*') {
            ans = is_match(p + 1, q, s, t)
                || is_match(p, q + 1, s, t);
        } else if (s[p] == t[q]) {
            ans = is_match(p + 1, q + 1, s, t);
        }
    }
    return ans;
}

bool is_match(const char * s, const char * t)
{
    memset(dp, -1, sizeof(dp));
    return is_match(0, 0, s, t);
}  

int main(int argc, char * argv[])
{
    if (is_match(argv[1], argv[2]))
        cout << "match" << endl;
    else cout << "not match" << endl;
    return 0;
}
