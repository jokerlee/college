/*
2、	实现复数类的运算重载
    编写C++程序完成以下功能：
（1）	实现复数类的运算重载：＋，－，*，/，^（乘方）。

*/ 

#include <iostream>
#include <iomanip>

using namespace std;

//复数类 
class Complex
{
private:
    double real;
    double imgy;
public:
    void show()const;
    Complex( double r, double i );//Constructor 
    Complex operator+(Complex c2);//operator + overload
    Complex operator-(Complex c2);//operator - overload
    Complex operator*(Complex c2);//operator * overload
    Complex operator/(Complex c2);//operator / overload
    Complex operator^(int n);//operator ^ overload
    double rval(){ return real; }
    double ival(){ return imgy; }
};

Complex::Complex( double r, double i )
{
    real = r;
    imgy = i;
    
}

Complex Complex::operator+(Complex c2)
{
    return Complex(real+c2.real,imgy+c2.imgy);
}

Complex Complex::operator-(Complex c2)
{
    return Complex(real-c2.real,imgy-c2.imgy);
}

Complex Complex::operator*(Complex c2)
{
    return Complex(real*c2.real-imgy*c2.imgy,c2.real*imgy+real*c2.imgy);
}

Complex Complex::operator/(Complex c2)
{
    return Complex((real*c2.real+imgy*c2.imgy)/(c2.real*c2.real+c2.imgy*c2.imgy),(c2.real*imgy-real*c2.imgy)/(c2.real*c2.real+c2.imgy*c2.imgy));
}

Complex Complex::operator^( int n )
{
    Complex c(real,imgy);
    while ( n > 1 )
    {
	    double a = c.real*real - c.imgy*imgy;
       	double b = real*c.imgy + c.real*imgy;
       	c.real = a;
       	c.imgy = b;
       	n--;
    }
    return c;
}

void Complex::show()const
{
    cout << real;
    cout.setf(ios_base::showpos);
    cout << imgy << "i" << endl;
    cout.setf(initial());
}


int main()
{
    double r1, r2, i1, i2;
    int n;
    
    cout << "请输入复数1：";
    cin >> r1 >> i1;
    cout << "请输入复数2：";
    cin >> r2 >> i2;
    
    cout<< "请输入乘方的次数：";
    cin >> n;
    
    Complex c1(r1,i1), c2(r2,i2);
    Complex c3=c1+c2;
    cout << "c1+c2 = ";
    c3.show();

    c3=c1-c2;
    cout << "c1-c2 = ";
    c3.show();

    c3=c1*c2;
    cout<<"c1*c2 = ";
    c3.show();

    c3=c1/c2;
    cout<<"c1/c2 = ";
    c3.show();
    
    c3=c1^n;
    cout<< "c1^"<<n<<" = ";
    c3.show();
    
    system("pause");
    return 0;
}
