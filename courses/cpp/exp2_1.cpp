/*
1��	����
��дC++����������¹��ܣ�
��1��	����һ��Point�࣬�����԰���������꣬�ṩ��������֮�����ķ�����
��2��	����һ�������࣬�����԰������ϽǺ����½������㣬�ṩ��������ķ�����
��3��	����һ�����ζ�����ʾ�û�����������ϽǺ����½ǵ����ꣻ
��4��	�۲���ζ����Լ�Point���Ա�Ĺ��캯�������������ĵ��ã�
��5��	������������������

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
{//�ÿ���������ڹ۲������������� 
	double x1, x2, y1, y2;
	cout << "�������1������ x y:" << endl;
	cin  >> x1 >> y1;
	cout << "�������2������ x y:" << endl;
	cin  >> x2 >> y2;
	
	Point p1(x1,y1), p2(x2,y2);
	cout << "���������: " << p1.dist(p2) << endl;

	cout << "������������Ͻ����� x y:" << endl;
	cin  >> x1 >> y1;
	cout << "������������½����� x y:" << endl;
	cin  >> x2 >> y2;	
	
	Rectangle r1( x1,y1,x2,y2 );
	cout << "���������: " << r1.area() << endl;	
}	
	system( "pause" );
	return 0;
}
