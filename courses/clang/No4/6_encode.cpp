/*
  Name: 6.������λ�� 
  Copyright:Free
  Author: Joker Lee 
  Date: 29/10/07 23:25
  Description: ����λ�����м���:ÿλ��+7 mod10;һ��λ������λ���� 
  �㷨 ������ÿһλ ����������װ 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
      int num;
      int a, b, c, d;//�ֱ����ڴ���ԭ����ǧλ����λ����λ 
      int result; //�����Ľ�� 
      
      printf ("������Ҫ���ܵ���λ��:");
      scanf ("%d", &num);
      
      a = (num/1000 + 7)%10;//������λ����ÿһλ��+7 ,mod 10 
      b = (num%1000/100 +7)%10;
      c = (num%100/10 + 7)%10;
      d = (num%10 + 7)%10;
      result = c*1000 + d*100 + a*10 + b;//��Ҫ���� 
      
      printf ("���ܺ������Ϊ��%d\n", result);
      printf ("���ܺ������Ϊ��%d\n", num);
            
      system ("pause");
      return 0;         
}
