/*
1、	猜价格游戏
编写C++程序完成以下功能：
（1）	假定有一件商品，程序用随机数指定该商品的价格（1-1000的整数）；
（2）	提示用户猜价格，并输入：若用户猜的价格比商品价格高或低，对用户作出相应的提示；
（3）	直到猜对为止，并给出提示。
*/

#include <iostream>
using namespace std;

int main()
{
	srand(time(NULL)); // initail random seed
	int num = rand()%1000+1, n;
	cout << "Here is a commodity, please guess its price:" << endl;
	while ( cin >> n && n != num )
	    if ( n > num )
	        cout << "high" << endl;
		else
		    cout << "low" << endl;
	cout << "You guess it. Congratulations!" << endl;
	
	system( "pause" );
	return 0;
}
