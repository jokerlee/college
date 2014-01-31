/*
6、	计算Fibonacci级数
fib(1) = fib(2) = 1
fib(n) = fib(n-1) + fib(n-2)
非递归版 
（1）	提示用户输入整数n；
（2）	fib(n)，并输出结果。
*/

#include <iostream>
using namespace std;

int fib( int n )
{
	if ( n==1 || n==2 )
	    return 1;
	int i=1, j=1, k, tmp;
	for ( k=3; k<n; k++ )//迭代计算数列项 
	{
		tmp = j;
		j = i+j;
		i = tmp;
	}
	return i+j;
}
int main()
{
    int n;
	cout << "请输入正整数n：";
	cin >> n;
	cout << fib(n) << endl;

	system("pause");
	return 0;
	
}
