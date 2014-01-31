/*
2��	��״������--�麯��
��1��	������״��һ���� �еĻ����������ķ�������Ϊ�麯�����Ƚ��롾��״��һ��������Ĳ��죻
��2��	������״��һ�����еĻ��ඨ������࣬�Ƚ��롾��״��һ��������Ĳ��졣
*/

#include <iostream>
using namespace std;

const double pi = 3.141592653;

class BaseShape//abstract base class
{
private:
public:
    BaseShape(){ cout << "BaseShape Constructor" << endl; }
    ~BaseShape(){ cout << "BaseShape Destructor" << endl; }
    virtual double area()const = 0;  // pure virtual method
};

class Rectangle: public BaseShape
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

class Circle: public BaseShape
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
    double l, w, rr;
    BaseShape *r,*c,*s;
    
    cout << "������γ��Ϳ�:";
    cin >> l >> w;
    r = new Rectangle( l, w );
    cout << "���ε����Ϊ��" << r->area() << endl;
    delete r;

    cout << "���������α߳�:";
    cin >> l;
    s = new Square(l);
    cout << "�����ε����Ϊ��" << s->area() << endl;
    delete s;

    cout << "����Բ�İ뾶:";
    cin >> rr;
    c = new Circle( rr );
    cout << "Բ�������" << c->area() << endl;
    delete c;

    system("pause");
    return 0;
}
