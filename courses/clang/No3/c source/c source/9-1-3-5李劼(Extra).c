//�ж�x�Ƿ�Ϊͬ����(��,5��25,6��36,25��625,etc)


#include <stdio.h> 
#include <stdlib.h> 

int main() 
{
      int num;
      
      printf ("input x\n");
      scanf ("%d", &num);
      
      if (num < 1 || num > 100)
            printf ("x out of range");
                 
      else if (num < 10){
            if ((num*num)%10 == num){
                  printf ("Yes");
            }
      }      
      else if ((num*num)%100 == num)
                  printf ("Yes");   
            else printf ("No");         
                           
      system ("pause");
      return 0;                           
}
