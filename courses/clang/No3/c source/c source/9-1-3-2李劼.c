//7.输入两个整数的最大公约数和最小公倍数(辗转相除求最大公约数)


#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int n1, n2;
      int max, min;
      int mdiv, mmul, temp = 0;//temp为中间变量 
    
      printf ("Plaes input two integers separated by spaces:\n");
      scanf ("%d %d", &n1, &n2);
    
      if (n1 > n2){//将较大数存于max;较小数存于min    
            max = n1;
            min = n2;
      }
      
      else if (n1 == n2){ //处理两数相等  
        max = min = n1;
      }
      
      else if (n1 < n2){
         max = n2;
         min = n1;
      }
    
      do{//b与a的相除的余数肯定含有最小公倍数,辗转相除                    
            temp = max;        
            max = min;    
            min = temp%min;
      }while (min != 0); 

      mdiv = max;
      mmul = n1*n2/mdiv;//最小公倍数等于两个数的积除以最大公约数 
    
      printf ("The max common divisor is:%d\n", mdiv);
      printf ("The min common multipul is:%d", mmul);
    
      system ("pause");
      return 0;
}
