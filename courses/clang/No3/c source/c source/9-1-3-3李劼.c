//6.��һԪ���η��̵ĸ�,�ֳ�ʵ����������ȸ�������� 


#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>

int main() 
{ 
      float a, b, c;
      float d, e, delta, root1, root2;//a,b,cΪϵ��,d���м����,eΪ������鲿,rootΪ�� 
    
      printf ("a,b,c=");
      scanf ("%f,%f,%f", &a, &b, &c);
    
      if (fabs(a) <= 1e-6)//����a=0 
            printf ("The equation is not quadratic.\n");
    
      else{
         
            delta = b*b - 4*a*c;
    
            if (delta < 0){//������� 
                  e = sqrt(-delta)/(2*a);
                  root1 = -b/(2*a);
                  printf ("The equation has complex roots:\n%f+%fi\n%f-%fi\n", root1, e, root1,e);    
            }
        
            else{
                  d = sqrt(delta);//�����������ֵ�����м���� 
                  root1 = (-b + d)/(2*a);
                  root2 = (-b - d)/(2*a);
    
                  if (fabs(delta) <= 1e-6)//����������� 
                        printf ("The equation has two equal roots:%f\n", root1);
    
                  else if (delta > 0)//��������ͬʵ�� 
                        printf ("The equation has distinct real roots:%f and %f\n", root1, root2);  
            }
      }
        
    system ("pause");
    return 0;
        
    
}
       
