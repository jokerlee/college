/* 
1��	��Point�����أ����ͨD�D�����
    ��дC++����������¹��ܣ�
��1��	Point������԰���������꣨x��y����
��2��	ʵ�� Point�����أ����ͨD�D�������
 	++p��--p��p++��p--��
 	�����ͨD�D�ֱ��ʾx��y���ӻ����1��
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
		Point operator++();//����ǰ��++ 
		Point operator--();//����ǰ��-- 
		Point operator++(int);//���غ���++ 
		Point operator--(int);//���غ���-- 
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

    cout << "������������(x,y):";
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
