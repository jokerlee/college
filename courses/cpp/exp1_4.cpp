/*
4、	乘法口诀表
编写C++程序完成以下功能：
（1）	输出乘法口诀表；
（2）	右对齐显示； 
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int i=1, j=1, n=0;
    
    for ( i=1; i<=9; i++ )
    {
		for ( j=1; j<i; j++ )//行前缩进 
		    cout << "        "; 
		for ( j=i; j<=9; j++ )
		    cout << i << '*' << j << '=' << setw(4) << left << i*j;
		cout << endl;
	}
	
    system ("pause");
    return 0;
}
