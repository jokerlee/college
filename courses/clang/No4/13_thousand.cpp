/*
  Name:13.千分位 
  Copyright: free 
  Author: Joker Lee 
  Date: 31/10/06 21:40
  Description:  将输入的数从个位起，每三位之间加一个逗号 
*/
#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int  div=1;//除数,用于将数字三位三位地分开 
	int i=0;//储存数字的位数 
	int j=0, k = 0,;
	int result;//result用于储存分离后的三位 
      int num, tempnum;//tempnum用于计算位数 
      
      printf ("n=");
      scanf ("%d", &num);
      
      tempnum = num;
      while (tempnum/10){//用循环计算数字的位数储存于i 
            i++;
            tempnum/=10;
      }
                  
      while (j < i-i%3){//初始化第一个除数,如一个8位数,第一个除数为 1e6 
            div *= 10;
            j++;
      }      
      
      while (div > 0){
            result = num/div;
            printf ("%d", temp);
            if (num > 10000)//省去个位后的逗号 
                  printf (", ");   
            num %= div;//去除已经打印的部分 
            div /= 1000;
      }
      
      system ("pause");
      return 0;
}
