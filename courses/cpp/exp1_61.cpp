/*
6、	计算Fibonacci级数
fib(1) = fib(2) = 1
fib(n) = fib(n-1) + fib(n-2)
递归版 
（1）	提示用户输入整数n；
（2）	fib(n)，并输出结果。
*/

#include <iostream>
using namespace std;

int fib( int n )
{
	if ( n==1 || n==2 )
		return 1;
	else
	    return fib(n-1)+fib(n-2);
}

int main()
{
	int n;
	cout << "请输入正整数n：";
	cin >> n;
	cout << fib(n) << endl;
	system( "pause" );
	return 0;
}
