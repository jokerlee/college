/*
  Name: 二进制转化十进制 
  Copyright: Free 
  Author: Joker Lee 
  Date: 23/11/07 18:17
  Description: 用递归算法将二进制转化成十进制 
  递归思路:将101101转换成十进制,即把 10110转换成二进制再*2+1... 
  递推公式:convert(x)= {convert(x/10)*2+x%10 |x/10!=0; x |x/10=0}
*/
#include <stdio.h>
#include <stdlib.h>

long _convert(int);
int main()
{
	long bin;
	
	printf ("请输入二进制数:");
	scanf ("%d", &bin);
	
	printf ("对应的十进制数是:%ld\n", _convert(bin)); 
	
	system ("pause");
	return 0;	
}

long _convert(int x)//递归进行二进制转换 
{
	if (x/10==0){
		return x;
	}	
	else{
		return _convert(x/10)*2+x%10;
	}
}
