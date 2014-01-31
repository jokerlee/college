/*5.打印所有除以11等于各位数字平方和的三位数 
采用穷举法 */


#include <stdio.h> 
#include <stdlib.h> 

int main() 
{
	  int a=0, b=0, c=0, i, j=1;//a,b,c分别用于储存百位、十位、个位 
                                 //j为控制换行的计数器 
      for (i=100; i <= 999; i++){
		    a = i/100;//分离每位数 
            b = (i%100)/10;
            c = i%10;
        
            if ((i%11 == 0) && (i/11 == a*a + b*b + c*c)){//判断是否能被11整除以及是否符合条件 
		          printf ("%d\t", i);
		
                  if (j%4 == 0)//每行4个数 
		                printf ("\n");
		        
                  j++;
            }            		
	  }

	  system ("pause");
	  return 0;
}
