/* 
此题所给算法有误 
5、	函数指针
实现二分法求解方程。编写以下函数求方程 f(x)=0的解：
double RolveRoot(double (*pf)(double x), double a, double b, int n)；
其中pf是一个函数指针（指向f(x)），RolveRoot()，用来获得f(x)=0在区间[a，b]内的解，f(x)的形式如 f(x)=x*x-3x+6等。a,b指定了方程 f(x)=0解存在的区间。n是迭代次数，次数越多，精度越高。
二分法的步骤：
（1）	计算 f(a) 、f(b)、f((a+b)/2)；
（2）	若f(a)与f((a+b)/2)异号，则在[a，(a+b)/2]区间内有解，令b = (a+b)/2, 回到第一步继续迭代，直到到达足够精度；
（3）	否则，令a = (a+b)/2, 回到第一步继续迭代，直到到达足够精度。
实现RolveRoot()，并采用不同 f(x) 验证。
*/ 

#include <iostream>
using namespace std;
int a, b, c;

inline double dabs( double x )//double绝对值 
{
    return x>0?x:-x;
}

double f( double x )// 
{
    return a*x*x-b*x+c;
}

double RolveRoot(double (*f)(double x), double a, double b, int n )
{
    do
    {
        if ( (*f)(a)*(*f)((a+b)/2) <= 0 )
            b = (a+b)/2;
        else
            a = (a+b)/2;
    }while ( n-- );
    return a;
        
}

int main()
{
	int l, r;
	cout << "请输入一元二次方程的二次项系数 一次项系数 常系数:" << endl;
 	cin >> a >> b >> c;
 	cout << "请输入根的范围:" << endl;	
 	cin >> l >> r;
    cout << "方程的解为:" << RolveRoot( &f, -l, r, 1000 ) << endl;
    system( "pause" );
    return 0;
}
