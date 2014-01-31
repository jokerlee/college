//2.判断输入的字母是否连续
#include<stdio.h>
#include<stdlib.h>

main()
{
      char a, b, c;
	  int d=0,e=0;
      
      printf ("Please enter 3 letters: ");
      scanf ("%c%c%c", &a, &b, &c);
      
      d= ((a >= 65) && (a <= 90)) || ((a >= 97) && (a <= 122));
	  e= ((a == b - 1) && (a == c -2));
	  
	  if (d && e)
             printf ("The result is: Ture");
      else 
             printf ("The result is: False");
             
          
      system ("pause");
      return 0;
            
}
