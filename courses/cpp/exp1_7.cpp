/*
7��	����n �����õ¶���ʽ
��дC++����������¹��ܣ�
��1��	��ʾ�û���������n��ʵ��x��
��2��	Pn(x)������������
Pn(x) = 1	��n=0�� 
      = x	��n=1�� 
      = ((2*n-1)*x*P(n-1,x)-(n-1)*P(n-2,x))/n	(n>1)
*/ 

#include <iostream>
using namespace std;

double P( int n, double x )//����Pn(x)�ĵݹ麯�� 
{
    if ( n==0 )
        return 1;
    else if ( n==1 )
        return x;
    else
        return ((2*n-1)*x*P(n-1,x)-(n-1)*P(n-2,x))/n;
}

int main()
{
    int n;
    double x;
    cout << "����������n��ʵ��x:" << endl;
    cin >> n >> x;
    cout << P(n,x) << endl;
    system( "pause" );
    return 0;
}
