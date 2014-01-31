/* 
5、	最大公约数和最小公倍数
编写C++程序完成以下功能：
（1）	提示用户输入两个无符号整数；
（2）	计算两者的最大公约数和最小公倍数，并输出。
*/
 
#include <iostream>
using namespace std;

int gcd( int m, int n ) //求两个数最大公约数 
{
	if ( m < n )
	{
		int tmp = n;
		n = m;
		m = tmp;
	}
	while ( n != 0 )
	{
		int tmp = n;
		n = m%n;
		m = tmp;
	}
}

int main()
{
	int m ,n, t;
	cout << "请输入两个正整数M N:" << endl;
	cin >> m >> n;
	if ( m>0 && n>0 )
	{
		t = gcd( m, n );
		cout << "最大公约数：" << t << endl;
		cout << "最小公倍数：" << m*n/t << endl;
	}
	else
		cerr << "输入不符合要求" << endl;
		 
	system( "pause" );
	return 0;
	
}
