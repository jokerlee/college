#include <iostream> 
#include <cstring>
using namespace std;

int main()
{
    int dp[5][11];
    long long num[11][11];
    string s;
    int len = 0;

    cin >> s;
    len = s.size(); 

    /* preprocess the number */
    memset(num, 0, 11* 11 * sizeof(int));
    for (int i = 1; i <= len; ++i){
        for (int j = i; j <= len; ++j)
            num[i][j] = num[i][j-1] * 10 + s[j - 1]-'0';
    }
    
    /* initialization */
    memset(dp, 0x7f, 5*11*sizeof(int));
    for (int i = 1; i <= len ; ++i)
        dp[1][i] = num[1][i];

    /* dp[i][j] = min{dp[i-1][j-k]} * num[j-k+1][j]} 
     * k in [1, j-i+1] */
    for (int i = 2; i <= 4; ++i)
        for (int j = 1; j <= len; ++j)
            for (int k = 1; k <= j - i + 1; ++k)
            {
                int tmp = dp[i-1][j-k] * num[j-k+1][j];
                dp[i][j] = (dp[i][j] < tmp) ? dp[i][j] : tmp;
            }
    
    cout << dp[4][len] << endl;

    return 0;
}
