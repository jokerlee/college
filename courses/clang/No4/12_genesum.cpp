#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int n, i=2, geneSum = 0;
    
      for (n=2; n <= 1000; n++){
            for (i=1; i < n ; i ++){//��ٷ��ҳ�n���������� 
                  if (n%i == 0)
                        geneSum += i; //�������Ӽ����ܺ� 
            }
            if (geneSum == n)
                  printf ("%d  ", n);
            geneSum = 0;//һ������ѭ������,���Ӻ͹��� 
      }
    
      system ("pause");
      return 0;
      
      
}
