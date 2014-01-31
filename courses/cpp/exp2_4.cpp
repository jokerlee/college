/*
4��	����
��дC++����������¹��ܣ�
��1��	����һ�������࣬���Ƕ�����˽������--���Ӻͷ�ĸ��
��2��	���������Ĺ��캯��������������
��3��	���巽��Set�����÷��Ӻͷ�ĸ��
��4��	���巽��print����ӡ��������ʽ�磺2/7��
��5��	���巽��value������double�͵ķ���ֵ��
��6��	���巽��invert, ���Ӻͷ�ĸ������
*/

#include <iostream>
#include <string>
using namespace std;

class Fraction
{
private:
	int denomin;
	int nomin;
public:
	Fraction( int x=1, int y=1 );
	~Fraction();
	void set( int x, int y );
	string show()const;//��ӡ���� 
	double value()const;//���ط�����ֵ 
	void invert();//���� 
};

Fraction::Fraction( int x, int y )
{
	if ( y!=0 )
		denomin = y;
	nomin = x;
}

Fraction::~Fraction()
{
}

void Fraction::set( int x, int y )
{
	nomin = x;
	denomin = y;
}

string Fraction::show()const
{
	char msg[100];
	sprintf( msg, "%d / %d", nomin, denomin );
	string a = msg;
	return a;
}

double Fraction::value()const
{
	return (double)nomin/denomin;
}

void Fraction::invert()
{
	int tmp = denomin;
	denomin = nomin;
	nomin = tmp;
}


int main()
{
	int a, b;
	
	cout << "���������1(���� ��ĸ):" << endl; 
	cin >> a >> b;
	Fraction f1( a,b );
	cout << "���������2(���� ��ĸ):" << endl;
	cin >> a >> b;
	Fraction f2( a,b );
	cout << "=====================================" << endl;
	cout << "����1��" << f1.show() << endl
		 << "����1��ֵ��" << f1.value() << endl;
	cout << "����2��" << f2.show() << endl
		 << "����2��ֵ��" << f2.value() << endl;
	cout << "=====================================" << endl;
	f2.invert();
	cout << "����2ȡ��" << endl
		 << "����2��" << f2.show() << endl
		 << "����2��ֵ��" << f2.value() << endl;

	system("pause");
	return 0;
}
