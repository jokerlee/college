/*
  Name: e^x 
  Copyright:Free 
  Author: Joker Lee 
  Date: 29/10/07 23:25
  Description: ʹ�õ�����,��̩�ռ���չ��,����e��x�η�
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
      int i=1; //iΪ��ǰ���� 
      float n=1, x, p=1;//p��̩�ռ�����ÿһ�� 
     
      printf ("Please input x:"); 
      scanf ("%f",&x);
      
      while (fabs(p) > 1e-8 ){ 
            p = p*x/i;//ͨ��ǰһ����ǰ�� 
            n = n + p;//�������ܺ� 
            i++;
      }
     
      printf ("%f",n);
     
      system("pause");
      return 0;
}
