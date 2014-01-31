//12.求一个数的所有因子之和 


#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int num, i=2, sum = 0;
    
      printf ("Please input n:");
      scanf ("%d", &num);
    
      if (num <= 0){//排除输入错误 
            printf ("Input error");
      }
      else{ 
            for (i=2; i < num; i ++){//穷举法找出n的所有因子 
                  if (num%i == 0)
                        sum += i;
            }
      }
      
      printf ("Sum = %d", sum);
    
      system ("pause");
      return 0;
      
      
}
