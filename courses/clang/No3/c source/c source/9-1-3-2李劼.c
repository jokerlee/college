//7.�����������������Լ������С������(շת��������Լ��)


#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int n1, n2;
      int max, min;
      int mdiv, mmul, temp = 0;//tempΪ�м���� 
    
      printf ("Plaes input two integers separated by spaces:\n");
      scanf ("%d %d", &n1, &n2);
    
      if (n1 > n2){//���ϴ�������max;��С������min    
            max = n1;
            min = n2;
      }
      
      else if (n1 == n2){ //�����������  
        max = min = n1;
      }
      
      else if (n1 < n2){
         max = n2;
         min = n1;
      }
    
      do{//b��a������������϶�������С������,շת���                    
            temp = max;        
            max = min;    
            min = temp%min;
      }while (min != 0); 

      mdiv = max;
      mmul = n1*n2/mdiv;//��С�����������������Ļ��������Լ�� 
    
      printf ("The max common divisor is:%d\n", mdiv);
      printf ("The min common multipul is:%d", mmul);
    
      system ("pause");
      return 0;
}
