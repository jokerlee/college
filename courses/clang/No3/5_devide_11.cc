//5.��ӡ���г���11���ڸ�λ����ƽ���͵���λ�� 


#include <stdio.h> 
#include <stdlib.h> 

int main() 
{
	  int a=0, b=0, c=0, i, j=1;
    
      for (i=100; i <= 999; i++){
		    a = i/100;
            b = (i%100)/10;
            c = i%10;
        
            if ((i%11 == 0) && (i/11 == a*a + b*b + c*c)){
		          printf ("%d\t", i);
		
                  if (j%4 == 0)//ÿ��4���� 
		                printf ("\n");
		        
                  j++;
            }            		
	  }

	  system ("pause");
	  return 0;
}
