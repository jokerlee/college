/* 
5��	���Լ������С������
��дC++����������¹��ܣ�
��1��	��ʾ�û����������޷���������
��2��	�������ߵ����Լ������С���������������
*/
 
#include <iostream>
using namespace std;

int gcd( int m, int n ) //�����������Լ�� 
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
	cout << "����������������M N:" << endl;
	cin >> m >> n;
	if ( m>0 && n>0 )
	{
		t = gcd( m, n );
		cout << "���Լ����" << t << endl;
		cout << "��С��������" << m*n/t << endl;
	}
	else
		cerr << "���벻����Ҫ��" << endl;
		 
	system( "pause" );
	return 0;
	
}
