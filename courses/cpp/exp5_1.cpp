/* 
1、	对Point类重载＋＋和――运算符
    编写C++程序完成以下功能：
（1）	Point类的属性包括点的坐标（x，y）；
（2）	实现 Point类重载＋＋和――运算符：
 	++p，--p，p++，p--。
 	＋＋和――分别表示x，y增加或减少1。
*/ 

#include <iostream>
#include <cmath>

const double pi = 3.141592654;
using namespace std;

/*==============CLASS POINT==============*/
class Point
{
	private:
		double x;
		double y;
	public:
		Point( double xx=0, double yy=0 );
		void show_point()const;
		Point operator++();//重载前置++ 
		Point operator--();//重载前置-- 
		Point operator++(int);//重载后置++ 
		Point operator--(int);//重载后置-- 
};
//constructor
Point::Point( double xx, double yy )
{
	x = xx;
	y = yy;
}

void Point::show_point()const
{
    cout << "(" << x << "," << y << ")";
}

Point Point::operator++()
{
    x++;
    y++;
    return *this;
}

Point Point::operator--()
{
    x--;
    y--;
    return *this;
}

Point Point::operator++(int)
{
	Point tmp = *this;
    ++(*this);
    return tmp;
}

Point Point::operator--(int)
{
	Point tmp = *this;
    --(*this);
    return tmp;
}
int main()
{
	double x, y;

    cout << "请输入点的坐标(x,y):";
    cin >> x >> y;
    Point p(x,y);

    cout << "Point++ = ";
    (p++).show_point();
    cout << endl;
    
    cout<< "++Point = ";
    (++p).show_point();
    cout << endl;
    
    cout<< "Point-- = ";
    (p--).show_point();
    cout << endl;
    
    cout<< "--Point = ";
    (--p).show_point();
    cout << endl;

	system( "pause" );
	return 0;
}
