/*
  Name: 数字进制转换 
  Copyright: Free 
  Author: Joker Lee 
  Date: 21-11-07 17:49
  Description: 将10进制的整数转换成任意进制 
*/

#include<stdio.h>
#include<stdlib.h>

void _convert(int ,int);
int main()
{
      int num, bit;
      
      printf ("请输入要转换的进制和待转换的十进制数(进制,十进制数):\n");
      scanf ("%d,%d", &bit, &num);
      
      printf("转换后%d进制数是", bit);
      _convert(num, bit);//调用函数转换并打印 

      system("pause");
      return 0;
}
             
void _convert(int num, int n)
{
      int bitN=1;
      
      //求最高位的位值 
      while (num >= bitN)
          bitN=bitN*n;                                 
      bitN=bitN/n;                                        
     
      //转换 
      while (bitN != 0) {
            if (num/bitN < 10)
                  printf("%d", num/bitN);
            else//处理16进制 
                  printf("%c", 'A'-10 + num/bitN); 
      
            num -= (num/bitN)*bitN;
            bitN = bitN/n;//下一位的位值 
      }  
      printf ("\n");
}
