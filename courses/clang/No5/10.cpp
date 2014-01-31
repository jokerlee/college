/*
  Name: 解一元三次方程 
  Copyright: Free 
  Author: Joker Lee 
  Date: 04/11/07 13:43
  Description: 用牛顿迭代法解一元三次方程 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	float x=0, x1=1, dfx, fx;//fx为方程的函数,dfx为导函数 
	float a, b, c, d;//a,b,c,d分别为方程的四个系数 
	
	printf ("plase input the a=");
	scanf ("%f", &a);
	printf ("plase input the b=");
	scanf ("%f", &b);
	printf ("plase input the c=");
	scanf ("%f", &c);
	printf ("plase input the d=");
	scanf ("%f", &d);
	
	while (fabs(x1-x) > 1e-5){
		x = x1;
		fx = a*x*x*x + b*x*x + c*x +d;
		dfx = 3*a*x*x + 2*b*x + c;
		x1 = x - fx/dfx;

	}
	printf ("the root is %f", x1);
	
	system ("pause");
	return 0;
}
