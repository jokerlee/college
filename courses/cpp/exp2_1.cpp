/*
1、	矩形
编写C++程序完成以下功能：
（1）	定义一个Point类，其属性包括点的坐标，提供计算两点之间距离的方法；
（2）	定义一个矩形类，其属性包括左上角和右下角两个点，提供计算面积的方法；
（3）	创建一个矩形对象，提示用户输入矩形左上角和右下角的坐标；
（4）	观察矩形对象以及Point类成员的构造函数与析构函数的调用；
（5）	计算其面积，并输出。

*/

#include <iostream>
#include <cmath>
using namespace std;
/* =======Point Class Declaration========== */
class Point
{
	private:
		double x;
		double y;
	public:
		Point( double xx=0, double yy=0 );//Constructor
		~Point();//destructor
		double xval()const;
		double yval()const;
		void set_x( double );
		void set_y( double );
		double dist( const Point )const;
};
//constructor
Point::Point( double xx, double yy )
{
	x = xx;
	y = yy;
	cout << "Point Class Constructor" << endl;
}

Point::~Point()
{
	cout << "Point Class Destructor" << endl;
}

double Point::xval()const
{
	return x;
}

double Point::yval()const
{
	return y;	
}

void Point::set_x( double xx )
{
	x = xx;
}

void Point::set_y( double yy )
{
	y = yy;	
}

double Point::dist( const Point b )const
{
	return sqrt( (x-b.xval())*(x-b.xval()) + (y-b.yval())*(y-b.yval()) );
}

/* =======Rectangle Class Declaration========== */

class Rectangle
{
	private:
		Point tlc; // top left coner
		Point brc; // bottom right coner
	public:
		Rectangle( double a, double b, double c, double d );
		~Rectangle();
		double area()const;
};
//constructor
Rectangle::Rectangle( double a, double b, double c, double d )
{
	tlc.set_x(a);
	tlc.set_y(b);
	brc.set_x(c);
	brc.set_y(d);
	cout << "Rectangle Class Constructor" << endl;	
}

Rectangle::~Rectangle()
{
	cout << "Rectangle Class Destructor" << endl;	
}

double Rectangle::area()const
{
	return (tlc.yval()-brc.yval())*(brc.xval()-tlc.xval());
}

int main()
{
{//用块包起来便于观察析构函数调用 
	double x1, x2, y1, y2;
	cout << "请输入点1的坐标 x y:" << endl;
	cin  >> x1 >> y1;
	cout << "请输入点2的坐标 x y:" << endl;
	cin  >> x2 >> y2;
	
	Point p1(x1,y1), p2(x2,y2);
	cout << "两点距离是: " << p1.dist(p2) << endl;

	cout << "请输入矩形左上角坐标 x y:" << endl;
	cin  >> x1 >> y1;
	cout << "请输入矩形右下角坐标 x y:" << endl;
	cin  >> x2 >> y2;	
	
	Rectangle r1( x1,y1,x2,y2 );
	cout << "矩形面积是: " << r1.area() << endl;	
}	
	system( "pause" );
	return 0;
}
