//5.输入一个数,将其每位拆开打印 

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
main()
{
      unsigned int num, a, counter = 0;
      
      printf ("Please input an int number:");
      scanf ("%d", &num);
      
      a = num;
	  while (a /=10)//a= a/10>0
		  counter++;

	  printf ("The result is: ");
	  counter = pow(10,counter);
      while (counter/10)
          {
		  printf ("%d ", num/counter);
          num -= (num/counter*counter);
		  counter/=10;
}
      printf ("%d" , num);
      
         
      system ("pause");
      return 0;
      }
