/*
7、	计算n 阶勒让德多项式
编写C++程序完成以下功能：
（1）	提示用户输入整数n和实数x；
（2）	Pn(x)，并输出结果。
Pn(x) = 1	（n=0） 
      = x	（n=1） 
      = ((2*n-1)*x*P(n-1,x)-(n-1)*P(n-2,x))/n	(n>1)
*/ 

#include <iostream>
using namespace std;

double P( int n, double x )//计算Pn(x)的递归函数 
{
    if ( n==0 )
        return 1;
    else if ( n==1 )
        return x;
    else
        return ((2*n-1)*x*P(n-1,x)-(n-1)*P(n-2,x))/n;
}

int main()
{
    int n;
    double x;
    cout << "请输入整数n和实数x:" << endl;
    cin >> n >> x;
    cout << P(n,x) << endl;
    system( "pause" );
    return 0;
}
