/*
  Name: �����Լ�� 
  Copyright: Free
  Author: Joker Lee 
  Date: 23/11/07 15:57
  Description:�������������Լ�� ���ݹ��㷨�� 
  ���ƹ�ʽ:GCD(x,y)= {gcd(y,x % y) |x%y!=0; y |x%y!=0} 
*/
#include <stdio.h>
#include <stdlib.h>

int _gcd(int, int);
int main()
{
	int num, max, min;
	
	printf ("������������(n1,n2)��\n");
	scanf ("%d,%d", &max, &min);
	
	if (min > max){
		min = min + max;
		max = min - max;
		min = min - max;
	}
	printf ("%d��%d�����Լ���ǣ�%d\n", min, max, _gcd(max,min));
	
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
