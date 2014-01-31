/* 
3、	流式IO（三）
编写C++程序完成以下功能：
（1）	输入一个文本文件名；
（2）	打开文件名，在该文件的每一行前面加上一个行号，保存在另外一个文本文件中。
*/ 

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string line;
    char filename[100];
    cout << "请输入源文件名：";
    cin >> filename;
    ifstream fin( filename, ios_base::in );
    ofstream fout( "out.txt", ios_base::out );
    int i=1;
    if ( fin )
    {
	    while ( fin )
	    {
	        getline(fin, line);
	        fout << i++ << " " << line << endl;
	    }
	    cout << "编辑完毕,结果保存在out.txt中" << endl;
	}
    else
        cerr << "文件打开失败" << endl;
    system( "pause" );
    return  0;
}
