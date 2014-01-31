#include <iostream>
#include <clocale>
#include <cwchar>
#include <cstdio>
#include <map>

using namespace std;


wchar_t puct[] = {L'，', L'。', L'、', L'！', L'？', L'￥', L'《', L'》', L'；', L'\0'};

int main()
{
    map<wstring, int> freq;
    setlocale(LC_ALL, "zh_CN.UTF-8");
    wchar_t buf[100] = {0};
    while (wscanf(L"%ls", buf) != EOF)
    {
        bool flg = false;
        for (int i = 0; i < 8; ++i)
        {
            if (puct[i] == buf[0])
            {
                flg = true;
                break;
            }
        }
        if (!flg) freq[buf]++;
    }
    
    map<wstring, int>::iterator i;
    for (i = freq.begin(); i != freq.end(); ++i)
    {
        wprintf(L"%ls %d\n", i->first.c_str(), i->second);
    }

    return 0;
}
