/*
6��	����Fibonacci����
fib(1) = fib(2) = 1
fib(n) = fib(n-1) + fib(n-2)
�ݹ�� 
��1��	��ʾ�û���������n��
��2��	fib(n)������������
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
	cout << "������������n��";
	cin >> n;
	cout << fib(n) << endl;
	system( "pause" );
	return 0;
}
