/*
  Name: 2.Goldbach 2
  Copyright: Free 
  Author: Joker Lee
  Date: 29/10/07 23:07
  Description: ��һ������4��ż���ֽ��2������֮�� 
  �㷨�� ����n����n+(n-1)ѭ����n/2+(n/2),���Ӻ����ж��������Ƿ�Ϊ����,
         ����������,��ӡ 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prim(int n);//�˺��������ж�һ�����Ƿ�Ϊ���� 
int main()
{
      int num, i, isprim1, isprim2;
      
      printf ("Please input an even number n(n>4)");
      scanf ("%d", &num);   
      
      for (i=2; i <= num/2; i++){//ѭ����һ������ 
            isprim1 = is_prim(i);//���ú���,�ж��Ƿ������� 
            isprim2 = is_prim(num-i);
            if (isprim1 && isprim2 == 1)
                  printf("The two gene is: %d and %d\n", i, num-i);
      }
      system ("pause");
      return 0;     
}

int is_prim(int n)
{
      int i=2;
      int isprim;
      
      isprim = 1;//��ʼ�������Ϊ�� 
      while (i < n/2){
            if (n%i == 0)//һ��������,�޸��������Ϊ�� 
			isprim = 0;  
            i++;
      }     
      return isprim;  //���ر�� 
}
