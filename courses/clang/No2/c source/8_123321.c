//8.输入一个三位数,把这个数的百位与各位对调,输出对调后的数
#include<stdio.h>
#include<stdlib.h>

main()
{
      int a, b, c, num;
      
      printf ("Input n(100<=n<=999):");
      scanf ("%d", &num);
      
      a = num/100;
      b = num%100/10 ;
      c = num%10;
      
      printf ("The change result is:%d", c*100+b*10+a);
            
      system ("pause");
      return 0;
      
}
