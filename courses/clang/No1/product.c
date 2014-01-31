//input 2 integer and print their product
#include<stdio.h>
main()
{
      int integer1, integer2, product;
      printf ("Please input two integer(number1,number2):");
      scanf ("%d,%d", &integer1,&integer2);
      product = integer1 * integer2;
      printf ("the product is: %d", product);
      system ("pause");
      return 0;
      }
