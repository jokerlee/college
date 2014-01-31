// 3.输入x,y,打印出x的y次方 

#include<stdio.h>
#include<stdlib.h>

main()
{
      int x, y, result = 1, counter = 0;
      
      printf ("Please enter x:");
      scanf ("%d", &x);
      printf ("Please enter Y:");
      scanf ("%d", &y);
      
      while (counter < y)
            {result = result * x;
            counter ++;}
            
      printf ("The result is:%d", result);
      
      system ("pause");
      return 0;
                 
}
