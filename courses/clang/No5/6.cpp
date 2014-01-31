/*
  Name: 5.二进制转十进制(支持小数) 
  Copyright: Free 
  Author: Joker Lee 
  Date: 04/11/07 14:06
  Description: 输入一个二进制数,一个一个读入并保存成一个整数,记录小数点位,
  		   再将每一位乘以权并相加,得到十进制数 
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	long int bin = 0;//储存去掉小数点的二进制数 
	int i=0, j=0;//i储存小树点前的长度,j储存总长度 
	int flag;//表示是否已经取到小树点的标记  
	int div=1;//div为处理时用的除数
	float  p=1;//当前二进制数位的权值 
	float  dec=0; //为计算出的10进制数 
	char n;
	
	printf ("请输入一个二进制数(以#结束)：");
	n = getchar();
	
	if (n != ' '){//排除数前空格 干扰 
		while (n != '#'){//独到#号代表结束 
			if (n == '1')
				bin = bin*10 + 1;
			else if (n == '0')
				bin = bin*10;	

			if (n== '.')
				flag = 1;//一旦取道小数点,标记为1 
			if (flag != 1)
				i++;//计算小数点前位数 
						
			if (n != '.')
				j++;//记录整个二进制数长度 
			n = getchar();
					
		}
	}	
	for (; i>1; i--)//初始化最高位权值 
		p*=2;
	for (; j>1; j--)//初始化最高位的除数 
		div *= 10;
		
	while (div > 1){
		while (bin/div == 0){//处理数字中间的"0",如果此位为零,则此时bin/div=0 
			div /= 10;
			p /= 2;
		}
		dec += bin/div*p;
		
		bin %= div;//除去最高位 
		div /= 10;
		p /= 2;
	}
	
	printf ("%f", dec);	
	system ("pause");
	return 0;	
	
}
