/*
1、	形状（一）
编写C++程序完成以下功能：
（1）	声明一个基类Shape（形状），其中包含一个方法来计算面积；
（2）	从Shape派生两个类矩形和圆形；
（3）	从矩形派生正方形；
（4）	分别实现派生类构造函数、析构函数和其他方法；
（5）	创建派生类的对象，观察构造函数、析构函数调用次序；
（6）	不同对象计算面积。
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

//矩形类公有继承Shape类 
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

//正方形类公有继承矩形类 
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

//圆类公有继承Shape类
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
    
    cout << "请输入矩形的长和宽:";
    cin >> l >> w;
    Rectangle r(l,w);
    cout << "矩形的面积是:" <<  r.area() << endl;
    
    cout << "请输入正方形的边长:";
    cin >> l;
    Square s(l);
    cout << "正方形的面积是:" << s.area() << endl;

    cout << "请输入圆的半径:";
    cin >> l;
    Circle c(l);
    cout << "矩形的面积是:" <<  c.area() << endl;
}    
    system( "pause" );
    return 0;

}
