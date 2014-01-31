/*
  Name: e^x 
  Copyright:Free 
  Author: Joker Lee 
  Date: 29/10/07 23:25
  Description: 使用迭代法,用泰勒级数展开,计算e的x次方
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
      int i=1; //i为当前项数 
      float n=1, x, p=1;//p是泰勒级数的每一项 
     
      printf ("Please input x:"); 
      scanf ("%f",&x);
      
      while (fabs(p) > 1e-8 ){ 
            p = p*x/i;//通过前一项求当前项 
            n = n + p;//迭代求总和 
            i++;
      }
     
      printf ("%f",n);
     
      system("pause");
      return 0;
}
