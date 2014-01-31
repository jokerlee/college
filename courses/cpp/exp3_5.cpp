/* 
���������㷨���� 
5��	����ָ��
ʵ�ֶ��ַ���ⷽ�̡���д���º����󷽳� f(x)=0�Ľ⣺
double RolveRoot(double (*pf)(double x), double a, double b, int n)��
����pf��һ������ָ�루ָ��f(x)����RolveRoot()���������f(x)=0������[a��b]�ڵĽ⣬f(x)����ʽ�� f(x)=x*x-3x+6�ȡ�a,bָ���˷��� f(x)=0����ڵ����䡣n�ǵ�������������Խ�࣬����Խ�ߡ�
���ַ��Ĳ��裺
��1��	���� f(a) ��f(b)��f((a+b)/2)��
��2��	��f(a)��f((a+b)/2)��ţ�����[a��(a+b)/2]�������н⣬��b = (a+b)/2, �ص���һ������������ֱ�������㹻���ȣ�
��3��	������a = (a+b)/2, �ص���һ������������ֱ�������㹻���ȡ�
ʵ��RolveRoot()�������ò�ͬ f(x) ��֤��
*/ 

#include <iostream>
using namespace std;
int a, b, c;

inline double dabs( double x )//double����ֵ 
{
    return x>0?x:-x;
}

double f( double x )// 
{
    return a*x*x-b*x+c;
}

double RolveRoot(double (*f)(double x), double a, double b, int n )
{
    do
    {
        if ( (*f)(a)*(*f)((a+b)/2) <= 0 )
            b = (a+b)/2;
        else
            a = (a+b)/2;
    }while ( n-- );
    return a;
        
}

int main()
{
	int l, r;
	cout << "������һԪ���η��̵Ķ�����ϵ�� һ����ϵ�� ��ϵ��:" << endl;
 	cin >> a >> b >> c;
 	cout << "��������ķ�Χ:" << endl;	
 	cin >> l >> r;
    cout << "���̵Ľ�Ϊ:" << RolveRoot( &f, -l, r, 1000 ) << endl;
    system( "pause" );
    return 0;
}
