/* 
2、	圆形
编写C++程序完成以下功能：
（1）	定义一个Point类，其属性包括点的坐标，提供计算两点之间距离的方法；
（2）	定义一个圆形类，其属性包括圆心和半径；
（3）	创建两个圆形对象，提示用户输入圆心坐标和半径，判断两个圆是否相交，并输出结果。
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
		Point( double xx=0, double yy=0 );//Constructor 
		~Point(){}
		double xval()const;//返回横坐标 
		double yval()const;//返回纵坐标 
		void set_x( double );//修改横坐标 
		void set_y( double );//修改纵坐标 
		double dist( const Point )const;//计算两点距离 
};

//constructor
Point::Point( double xx, double yy )
{
	x = xx;
	y = yy;
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


/*==============CLASS CIRCLE==============*/
class Circle
{
private:
	Point center;
	double radius;
public:
	Circle( double x=0, double y=0, double r=0 );
	double area()const;//计算圆的面积 
	void set_center( double x, double y );//设置圆心坐标 
	void set_radius( double r );//设置半径 
	bool isIntersect( const Circle )const;//判断两圆是不是相交 
};

Circle::Circle( double x, double y, double r )
{
	set_center( x, y );
	set_radius( r );
}

double Circle::area()const
{
	return pi*radius*radius;	
} 

void Circle::set_center( double x, double y )
{
	center.set_x(x);
	center.set_y(y);	
}

void Circle::set_radius( double r )
{
	radius = r;	
}

bool Circle::isIntersect( const Circle c1 )const
{
	return radius+c1.radius >= center.dist( c1.center ) 
		&& fabs(radius-c1.radius) <= center.dist( c1.center );	
}

/*==============================================*/ 

int main()
{
	double x1, x2, r1, y1, y2, r2;
	cout << "请输入圆1的圆心坐标和半径 x1 y1 r1:" << endl;
	cin  >> x1 >> y1 >> r1;
	cout << "请输入点2的圆心坐标和半径 x2 y2 r2:" << endl;
	cin  >> x2 >> y2 >> r2;
	Circle c1( x1, y1, r1), c2( x2, y2, r2 );
	if ( c1.isIntersect(c2) )
		cout << "两圆相交" << endl;
	else
		cout << "两圆不相交" << endl;
	
	system( "pause" );
	return 0;
}
