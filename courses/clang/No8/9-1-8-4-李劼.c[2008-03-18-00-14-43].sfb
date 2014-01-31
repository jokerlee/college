/*
  Name: 素数分解 
  Copyright: Free 
  Author: Joker Lee 
  Date: 23/11/07 20:44
  Description: 将素数分解成质因子并打印出来（递归） 
  递归思路:将20分解质因数,即先分解出最小质因子2后在对20/2进行分解 
*/
#include <stdio.h>
#include <stdlib.h>

int _primFact(int);
int main()
{
	int max, min, num;
	
	printf ("请输入判断范围(from,to):");
	scanf ("%d,%d", &min, &max);//读入判断范围 
	
	for (num=min; num<=max; num++){//分解范围内每个数 
		printf ("%d=", num);
		_primFact(num);//调用子函数 
		printf ("\n");
	} 
	
	system ("pause");
	return 0;
}

int _primFact(int x)
{
	int i;
	
	for (i=2; i<=x; i++){//分解出一个最小质因子 
		if (x%i==0){
			printf ("%d*",i);
			return _primFact(x/i);
		}
	}
	printf ("\b ");//去除行尾乘号 
}
