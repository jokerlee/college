/*
  Name: 求最大公约数 
  Copyright: Free
  Author: Joker Lee 
  Date: 23/11/07 15:57
  Description:求两个数的最大公约数 （递归算法） 
  递推公式:GCD(x,y)= {gcd(y,x % y) |x%y!=0; y |x%y!=0} 
*/
#include <stdio.h>
#include <stdlib.h>

int _gcd(int, int);
int main()
{
	int num, max, min;
	
	printf ("请输入两个数(n1,n2)：\n");
	scanf ("%d,%d", &max, &min);
	
	if (min > max){
		min = min + max;
		max = min - max;
		min = min - max;
	}
	printf ("%d和%d的最大公约数是：%d\n", min, max, _gcd(max,min));
	
	system ("pause");
	return 0;
} 

int _gcd(int x, int y)
{
	if (x%y == 0){
		return y;
	}
	else 
		return _gcd(y, x%y);
}
