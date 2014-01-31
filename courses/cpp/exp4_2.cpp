/*
2、	形状（二）--虚函数
（1）	将【形状（一）】 中的基类计算面积的方法定义为虚函数，比较与【形状（一）】程序的差异；
（2）	将【形状（一）】中的基类定义抽象类，比较与【形状（一）】程序的差异。
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
    
    cout << "输入矩形长和宽:";
    cin >> l >> w;
    r = new Rectangle( l, w );
    cout << "矩形的面积为：" << r->area() << endl;
    delete r;

    cout << "输入正方形边长:";
    cin >> l;
    s = new Square(l);
    cout << "正方形的面积为：" << s->area() << endl;
    delete s;

    cout << "输入圆的半径:";
    cin >> rr;
    c = new Circle( rr );
    cout << "圆的面积：" << c->area() << endl;
    delete c;

    system("pause");
    return 0;
}
