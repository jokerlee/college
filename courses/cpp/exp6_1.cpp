/*
1、	流式IO（一）
编写C++程序完成以下功能：
（1）	使用ofstream 向一个文本文件中输出各种类型的数据，并打开文件观察结果：
 	整数、无符号整型、长整型、浮点型、字符串、……
（2）	用十进制、八进制、十六进制方式向文本文件中输出整数；
（3）	使用控制符和成员函数来控制输出的格式：
 	set（） precision() ...
*/

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
		    
    ofstream fout( "61.txt" );
    fout << a << endl
         << c << endl
         << c << endl
         << setprecision(3) << d << endl
         << e << endl;
    fout << dec << a << endl
         << oct << a << endl
         << hex << a << endl;
    fout.close();
    cout << "输出完毕，结果保存在61.txt中" << endl;
    
    system( "pause" );
    return 0;
}
