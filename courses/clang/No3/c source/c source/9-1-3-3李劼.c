//6.求一元二次方程的根,分成实根、虚根、等根三种情况 


#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>

int main() 
{ 
      float a, b, c;
      float d, e, delta, root1, root2;//a,b,c为系数,d做中间变量,e为虚根的虚部,root为根 
    
      printf ("a,b,c=");
      scanf ("%f,%f,%f", &a, &b, &c);
    
      if (fabs(a) <= 1e-6)//处理a=0 
            printf ("The equation is not quadratic.\n");
    
      else{
         
            delta = b*b - 4*a*c;
    
            if (delta < 0){//处理虚根 
                  e = sqrt(-delta)/(2*a);
                  root1 = -b/(2*a);
                  printf ("The equation has complex roots:\n%f+%fi\n%f-%fi\n", root1, e, root1,e);    
            }
        
            else{
                  d = sqrt(delta);//将开方运算的值赋给中间变量 
                  root1 = (-b + d)/(2*a);
                  root2 = (-b - d)/(2*a);
    
                  if (fabs(delta) <= 1e-6)//处理两根相等 
                        printf ("The equation has two equal roots:%f\n", root1);
    
                  else if (delta > 0)//处理两不同实根 
                        printf ("The equation has distinct real roots:%f and %f\n", root1, root2);  
            }
      }
        
    system ("pause");
    return 0;
        
    
}
       
