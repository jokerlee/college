/*
1��	��״��һ��
��дC++����������¹��ܣ�
��1��	����һ������Shape����״�������а���һ�����������������
��2��	��Shape������������κ�Բ�Σ�
��3��	�Ӿ������������Σ�
��4��	�ֱ�ʵ�������๹�캯������������������������
��5��	����������Ķ��󣬹۲칹�캯���������������ô���
��6��	��ͬ������������
*/

#include <iostream>
using namespace std;

const double pi = 3.141592654;


class Shape
{
private:
public:
    Shape(){ cout << "Shape Constructor" << endl; }
    ~Shape(){ cout << "Shape Destructor" << endl; }
    double area()const{}
};

//�����๫�м̳�Shape�� 
class Rectangle: public Shape
{
private:
    double width;
    double length;
public:
    Rectangle( double l=0, double w=0 )
    { cout << "Rectangle Constructor" << endl; length = l; width = w; }
    ~Rectangle(){ cout << "Rectangle Destructor" << endl; }
    double area()const{ return width*length; }
};

//�������๫�м̳о����� 
class Square: public Rectangle
{
private:
    double side;
public:
    Square( double s=0 )
    {  cout << "Square Constructor" << endl; side=s; }
    ~Square(){  cout << "Square Destructor" << endl; }
    double area()const{ return side*side; }
};

//Բ�๫�м̳�Shape��
class Circle: public Shape
{
private:
    double radius;
public:
    Circle( double r )
    { cout << "Circle Constructor" << endl; radius = r; }
    ~Circle(){  cout << "Circle Destructor" << endl; }
    double area()const{ return pi*radius*radius; }
};

int main()
{
{
    double w, l;
    
    cout << "��������εĳ��Ϳ�:";
    cin >> l >> w;
    Rectangle r(l,w);
    cout << "���ε������:" <<  r.area() << endl;
    
    cout << "�����������εı߳�:";
    cin >> l;
    Square s(l);
    cout << "�����ε������:" << s.area() << endl;

    cout << "������Բ�İ뾶:";
    cin >> l;
    Circle c(l);
    cout << "���ε������:" <<  c.area() << endl;
}    
    system( "pause" );
    return 0;

}
