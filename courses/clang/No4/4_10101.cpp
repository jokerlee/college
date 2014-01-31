/*
  Name: 4.二进制转换 
  Copyright:  Free 
  Author: Joker Lee 
  Date: 31/10/07 11:28
  Description: 将输入的二进制数转化成10进制
  算法：（迭代法）将输入的二进制数存于一个字符串数组，从数组末尾逐个读取字符
        根据转换公式每位乘上权值加上上一步的值，每循环一次权值*2 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char num[128];
	int p=0, i=1, n=1;//n为当前位的权 
	
	printf ("请输入一个二进制数：");
	scanf ("%s", num);
	
	i = strlen(num);//获得二位数的长度,以控制循环次数 
	while (i>=0){
		if (num[i-1] == '1')//字符串数组末位为终止符null,所以从倒数第二位开始 
			p += 1*n;//迭代求总和 
		n *= 2;
		i --;
	}
	
	printf ("对应的十进制数为：%d", p);
	system ("pause");
	return 0;
}
