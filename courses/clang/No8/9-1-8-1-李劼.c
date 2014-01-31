/*
  Name: 二进制位数 
  Copyright: Free
  Author: Joker Lee 
  Date: 23/11/07 15:57
  Description:求给定个数的十进制数的二进制形式的位数 （递归） 
*/
#include <stdio.h>
#include <stdlib.h>

int _getDigit(int);
int main()
{
	int num, i, n;
	printf ("请输入正整数的个数：\n");
	scanf ("%d", &n);//读入要输入的整数的个数 
	printf ("请输入%d个正整数：\n", n);
	
	for (i=0; i<n; i++){//循环读入i个十进制整数 
		scanf ("%d,", &num); 
		if (i==0){//第一次循环打印提示 
			printf ("转换成二进制形式后的长度是：\n");
		}
		printf ("%d", _getDigit(num));		
		if (i != n-1){//最后一位不打印逗号 
			printf (",");
		}
		else printf ("\n");//打完最后一位后换行 
	} 
	system ("pause");
	return 0;
}

int _getDigit(int bit)//递归求二进制位数 
{
	if (bit/2 == 0){
		return 1;
	}	
	else
		return _getDigit(bit/2)+1;
}
