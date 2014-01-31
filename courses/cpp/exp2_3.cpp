/* 
3��	��Ԫ
��дC++����������¹��ܣ�
��1��	����һ��Boat��Car�����࣬���Ƕ�����˽������--������
��2��	��дһ���������������ߵ������͡�
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
	cout << "�����봬��������" << endl;
	cin >> w1;
	cout << "�����복��������" << endl;	
	cin >> w2;
	
	Boat b(w1);
	Car c(w2);
	
	cout << "���ͳ���������Ϊ:" << TotalWeight( c, b12 ) << endl;
	system( "pause" );
	return 0;
}
