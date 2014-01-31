/* 
2��	Բ��
��дC++����������¹��ܣ�
��1��	����һ��Point�࣬�����԰���������꣬�ṩ��������֮�����ķ�����
��2��	����һ��Բ���࣬�����԰���Բ�ĺͰ뾶��
��3��	��������Բ�ζ�����ʾ�û�����Բ������Ͱ뾶���ж�����Բ�Ƿ��ཻ������������
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
		double xval()const;//���غ����� 
		double yval()const;//���������� 
		void set_x( double );//�޸ĺ����� 
		void set_y( double );//�޸������� 
		double dist( const Point )const;//����������� 
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
	double area()const;//����Բ����� 
	void set_center( double x, double y );//����Բ������ 
	void set_radius( double r );//���ð뾶 
	bool isIntersect( const Circle )const;//�ж���Բ�ǲ����ཻ 
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
	cout << "������Բ1��Բ������Ͱ뾶 x1 y1 r1:" << endl;
	cin  >> x1 >> y1 >> r1;
	cout << "�������2��Բ������Ͱ뾶 x2 y2 r2:" << endl;
	cin  >> x2 >> y2 >> r2;
	Circle c1( x1, y1, r1), c2( x2, y2, r2 );
	if ( c1.isIntersect(c2) )
		cout << "��Բ�ཻ" << endl;
	else
		cout << "��Բ���ཻ" << endl;
	
	system( "pause" );
	return 0;
}
