//6.一到十的平方和立方 
#include<stdio.h>
#include<stdlib.h>

main()
{
      int i = 0;
      
      printf ("number\tsquare\tcube\t\n");
      for (i = 1; i <= 10;i ++)
          printf("%d\t%d\t%d\t\n", i, i*i, i*i*i);
      
      system ("pause");
      return 0;
      }
