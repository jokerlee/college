/*
  Name: 6.加密四位数 
  Copyright:Free
  Author: Joker Lee 
  Date: 29/10/07 23:25
  Description: 对四位数进行加密:每位数+7 mod10;一三位、二四位交换 
  算法 ：分离每一位 ，重新再组装 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
      int num;
      int a, b, c, d;//分别用于储存原数的千位、百位、各位 
      int result; //处理后的结果 
      
      printf ("请输入要加密的四位数:");
      scanf ("%d", &num);
      
      a = (num/1000 + 7)%10;//分离四位数的每一位并+7 ,mod 10 
      b = (num%1000/100 +7)%10;
      c = (num%100/10 + 7)%10;
      d = (num%10 + 7)%10;
      result = c*1000 + d*100 + a*10 + b;//按要求处理 
      
      printf ("加密后的整数为：%d\n", result);
      printf ("解密后的整数为：%d\n", num);
            
      system ("pause");
      return 0;         
}
