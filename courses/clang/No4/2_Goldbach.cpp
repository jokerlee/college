/*
  Name: 2.Goldbach 1
  Copyright:  Free 
  Author: Joker Lee
  Date: 29/10/07 23:07
  Description: 2.将一个大于4的偶数分解成2个素数之和 
  算法： 输入n，建立一个包含所有小于n素数的素数表，然后用穷举法列出组合 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int prim_list(int n,int str[102400]);//此函数用于建立素数表 
int main()
{
      int num; 
      int i, j;//分别用于控制循环素数表中的两个素数 
      int len, primList[102400];//len为素数表长度 
      
      printf ("Please input an even number n(n>4)");
      scanf ("%d", &num);
      
      len = prim_list(num, primList);//调用函数 
      
      for (i=0; i <= len/2; i++){//第一个素数,从素数表前端循环到中间
            for (j=0; j <= len; j++){//第二个素数,从素数表尾端循环到中间 
                  if (primList[i] + primList[j] == num)
                        printf ("The two gene is: %d and %d\n", primList[i],primList[len-i]);
                  }
      }
      
      system ("pause");
      return 0;     
}

int prim_list(int n, int str[102400])//n为素数上限，即num 
{
      int i=0, j=2, k=0;
      
      for (i=2; i <= n; i++){
            j=2; //除数归2 
            while ((j < i) && (i%j != 0))//j作除数,循环到i,一旦j可以整除i跳出 
                 j++;
            if (j == i){//如果循环结束时i=j,说明i是一个素数 
                  str[k]=i;
                  k++;
            }
      }
      return k;//返回数组(素数表)长度 
}
