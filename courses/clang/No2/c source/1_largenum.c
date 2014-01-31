//输入两个数，打印出其中较大数
#include<stdlib.h>
#include<stdio.h>

main()
{
      int num1, num2;
      
      printf ("Please enter two numbers");
      scanf ("%d%d", &num1, &num2);
      
      if (num1 >= num2)
          printf ("The large number is:%d", num1);
      else
          printf ("The large number is:%d", num2); 
          
          
      system("pause");
      return 0;         
}
