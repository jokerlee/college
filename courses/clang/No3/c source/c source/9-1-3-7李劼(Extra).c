//12.��һ��������������֮�� 


#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int num, i=2, sum = 0;
    
      printf ("Please input n:");
      scanf ("%d", &num);
    
      if (num <= 0){//�ų�������� 
            printf ("Input error");
      }
      else{ 
            for (i=2; i < num; i ++){//��ٷ��ҳ�n���������� 
                  if (num%i == 0)
                        sum += i;
            }
      }
      
      printf ("Sum = %d", sum);
    
      system ("pause");
      return 0;
      
      
}
