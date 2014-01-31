#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int n, i=2, geneSum = 0;
    
      for (n=2; n <= 1000; n++){
            for (i=1; i < n ; i ++){//穷举法找出n的所有因子 
                  if (n%i == 0)
                        geneSum += i; //若是因子加入总和 
            }
            if (geneSum == n)
                  printf ("%d  ", n);
            geneSum = 0;//一个数的循环结束,因子和归零 
      }
    
      system ("pause");
      return 0;
      
      
}
