//12.��һ��������������֮�� 


#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int n, i=2, sum = 0;
    
      printf ("Please input n:");
      scanf ("%d", &n);
    
      if (n <= 0){//�ų�������� 
            printf ("Input error");
      }
      else{ 
            for (i=2; i < n; i ++){//��ٷ��ҳ�n���������� 
                  if (n%i == 0)
                        sum += i;
            }
      }
      
      printf ("Sum = %d\n", sum);
    
      system ("pause");
      return 0;
      
      
}
