/*
  Name: 2.Goldbach 2
  Copyright: Free 
  Author: Joker Lee
  Date: 29/10/07 23:07
  Description: 把一个大于4的偶数分解成2个素数之和 
  算法： 输入n，从n+(n-1)循环到n/2+(n/2),用子函数判断两个数是否为素数,
         若都是素数,打印 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prim(int n);//此函数用于判断一个数是否为素数 
int main()
{
      int num, i, isprim1, isprim2;
      
      printf ("Please input an even number n(n>4)");
      scanf ("%d", &num);   
      
      for (i=2; i <= num/2; i++){//循环第一个素数 
            isprim1 = is_prim(i);//调用函数,判断是否是素数 
            isprim2 = is_prim(num-i);
            if (isprim1 && isprim2 == 1)
                  printf("The two gene is: %d and %d\n", i, num-i);
      }
      system ("pause");
      return 0;     
}

int is_prim(int n)
{
      int i=2;
      int isprim;
      
      isprim = 1;//初始素数标记为真 
      while (i < n/2){
            if (n%i == 0)//一旦能整除,修改素数标记为假 
			isprim = 0;  
            i++;
      }     
      return isprim;  //返回标记 
}
