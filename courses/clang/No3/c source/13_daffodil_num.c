//13.�ж�����������Ƿ�Ϊˮ�ɻ��� 


#include <stdio.h> 
#include <stdlib.h>

int main() 
{
      int a=0, b=0, c=0, n;// a,b,c�ֱ�洢��λ���İ�λ,ʮλ,��λ 

	  printf ("Please input n(100<=n<1000):\n");
      scanf ("%d", &n);
      
      a = n/100;//������λ����ÿһλ 
      b = (n%100)/10;
	  c = n%10;
	
      if (n == a*a*a + b*b*b + c*c*c)       
            printf ("%d��\"ˮ�ɻ���\"\n", n);
      else    
            printf ("%d����һ��\"ˮ�ɻ���\"\n", n); 

	  system ("pause");
	  return 0;
}
