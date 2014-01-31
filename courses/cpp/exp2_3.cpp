/* 
3、	友元
编写C++程序完成以下功能：
（1）	定义一个Boat和Car两个类，他们都具有私用属性--重量；
（2）	编写一个函数，计算两者的重量和。
double TotalWeight(Boat& b, Car& c);
*/
 
#include <iostream>


class Boat;
/*=============Class Car Declaration=============*/
class Car
{
private:
	double weight;	
public:
	Car( double w=0 )
	{
		weight = w;
	}	
	double weightVal()const
	{
		return weight;	
	}
	friend double TotalWeight( const Car&, const Boat& );	
};

/*=============Class Boat Declaration=============*/

class Boat
{
private:
	double weight;
public:
	Boat( double w=0 )
	{
		weight = w;
	}
	double weightVal()const
	{
		return weight;
	}
	friend double TotalWeight( const Car&, const Boat& );
};

double TotalWeight( const Car& c, const Boat& b )
{
	return c.weight + b.weight;
}

using namespace std;
int main()
{
	double w1, w2;
	cout << "请输入船的重量：" << endl;
	cin >> w1;
	cout << "请输入车的重量：" << endl;	
	cin >> w2;
	
	Boat b(w1);
	Car c(w2);
	
	cout << "船和车的总重量为:" << TotalWeight( c, b12 ) << endl;
	system( "pause" );
	return 0;
}
