/*
2、	流式IO（二）
编写C++程序完成以下功能：
（1）	输入一个文本文件名
（2）	使用ofstream 向一个二进制文件中输出各种类型的数据，并打开文件观察结果：
 	整数、无符号整型、长整型、浮点型、字符串、……
*/

#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int a;
	unsigned int b;
	long c;
	float d;
	char e[100];
	
    cout << "请输入一个整数:";
    cin  >> a;
    cout << "请输入一个正整数:";
    cin  >> b;    
    cout << "请输入一个长整数:";
    cin  >> c;
    cout << "请输入一个浮点数:";
    cin  >> d;
    cout << "请输入一个字符串:";
    cin  >> e;	
		    
    ofstream fout( "62.txt", ios_base::binary );
    fout << a << endl
         << c << endl
         << c << endl
         << setprecision(3) << d << endl
         << e << endl;
    fout << dec << a << endl
         << oct << a << endl
         << hex << a << endl;
    fout.close();
    cout << "输出完毕，结果保存在62.txt中" << endl;
    
    system( "pause" );
    return 0;
}
