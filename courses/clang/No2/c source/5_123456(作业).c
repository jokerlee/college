//5.输入一个数,将其每位拆开打印 

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
main()
{
      long num, a, counter = 0;
      
      printf ("Please input an int number:");
      scanf ("%d", &num);
      
      a = num;
	  while (a /=10){//此循环用于确定数字位数
		  counter++;}
		  

	  printf ("The result is: ");
	  counter = (float)pow(10,counter);//循环前初始化除数
      while (counter/10>0)//次循环用于打印每一位
          {
		  printf ("%l ", num/counter);
          num -= (num/counter*counter);//打印完后将数字的首位去除
		  counter/=10;
          }
      
      printf ("%l" , num);
      
         
      system ("pause");
      return 0;
      }
