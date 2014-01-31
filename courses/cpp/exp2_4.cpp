/*
4、	分数
编写C++程序完成以下功能：
（1）	定义一个分数类，他们都具有私用属性--分子和分母；
（2）	定义分数类的构造函数和析构函数；
（3）	定义方法Set，设置分子和分母；
（4）	定义方法print，打印分数，格式如：2/7；
（5）	定义方法value，返回double型的分数值；
（6）	定义方法invert, 分子和分母交换。
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
	string show()const;//打印分数 
	double value()const;//返回分数的值 
	void invert();//求倒数 
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
	
	cout << "请输入分数1(分子 分母):" << endl; 
	cin >> a >> b;
	Fraction f1( a,b );
	cout << "请输入分数2(分子 分母):" << endl;
	cin >> a >> b;
	Fraction f2( a,b );
	cout << "=====================================" << endl;
	cout << "分数1：" << f1.show() << endl
		 << "分数1的值：" << f1.value() << endl;
	cout << "分数2：" << f2.show() << endl
		 << "分数2的值：" << f2.value() << endl;
	cout << "=====================================" << endl;
	f2.invert();
	cout << "分数2取倒" << endl
		 << "分数2：" << f2.show() << endl
		 << "分数2的值：" << f2.value() << endl;

	system("pause");
	return 0;
}
