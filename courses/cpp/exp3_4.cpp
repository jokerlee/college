/*
4、	字符串翻转
编写C++程序完成以下功能：
（1）	输入一段字符串；
（2）	将字符串翻转以后输出（不要利用库函数）。
*/ 

#include <iostream>

using namespace std;

int main()
{
    char str[1000], *p, *q, tmp;
    cin.getline( str, 1000 );//读入源字符串 
    for ( q=str+0; *q!='\0'; q++ ) {}//找到字符串尾 
    for ( p=str+0, q--; q-p>=1; p++, q-- )
    {
        tmp = *p;
        *p = *q;
        *q = tmp;
    }
    cout << str << endl;
    system( "pause" );
    return 0;
}
