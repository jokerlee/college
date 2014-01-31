#include <iostream>
#include <vector>

using std::string;
using std::vector;


string str_unique(string str)
{
    string ret;
    bool flg[256] = {false};

    for (int i = 0; i < str.size(); ++i)
        if (!flg[str[i]])
        {
            flg[str[i]] = true;
            ret.push_back(str[i]);
        }
    return ret;
}

void search(vector<string> src, vector<string> & ret, int p, string & crnt)
{
    if (p == src.size())
    {
        ret.push_back(str_unique(crnt));
        return;
    }
    
    for (int i = 0; i < src[p].size(); ++i)
    {
        crnt.push_back(src[p][i]); 
        search(src, ret, p+1, crnt);
        crnt.erase(crnt.size()-1, 1);
    }
}

int main()
{
    vector<string> src, ret;
    string tmp;

    src.push_back("ab");
    src.push_back("ed");
    src.push_back("ad");

    search(src, ret, 0, tmp);

    for (int i = 0; i < ret.size(); ++i)
        std::cout << ret[i] << std::endl;

    return 0;

}
