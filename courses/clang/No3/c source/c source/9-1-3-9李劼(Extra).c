//13.判断输入的数字是否为水仙花数 


#include <stdio.h> 
#include <stdlib.h>

int main() 
{
      int a=0, b=0, c=0, n;// a,b,c分别存储三位数的百位,十位,各位 

	  printf ("Please input n(100<=n<1000):\n");
      scanf ("%d", &n);
      
      a = n/100;//分离三位数的每一位 
      b = (n%100)/10;
	  c = n%10;
	
      if (n == a*a*a + b*b*b + c*c*c)       
            printf ("%d是\"水仙花数\"\n", n);
      else    
            printf ("%d不是一个\"水仙花数\"\n", n); 

	  system ("pause");
	  return 0;
}
