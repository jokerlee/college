/*
  Name: 2.Goldbach 1
  Copyright:  Free 
  Author: Joker Lee
  Date: 29/10/07 23:07
  Description: 2.��һ������4��ż���ֽ��2������֮�� 
  �㷨�� ����n������һ����������С��n������������Ȼ������ٷ��г���� 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int prim_list(int n,int str[102400]);//�˺������ڽ��������� 
int main()
{
      int num; 
      int i, j;//�ֱ����ڿ���ѭ���������е��������� 
      int len, primList[102400];//lenΪ�������� 
      
      printf ("Please input an even number n(n>4)");
      scanf ("%d", &num);
      
      len = prim_list(num, primList);//���ú��� 
      
      for (i=0; i <= len/2; i++){//��һ������,��������ǰ��ѭ�����м�
            for (j=0; j <= len; j++){//�ڶ�������,��������β��ѭ�����м� 
                  if (primList[i] + primList[j] == num)
                        printf ("The two gene is: %d and %d\n", primList[i],primList[len-i]);
                  }
      }
      
      system ("pause");
      return 0;     
}

int prim_list(int n, int str[102400])//nΪ�������ޣ���num 
{
      int i=0, j=2, k=0;
      
      for (i=2; i <= n; i++){
            j=2; //������2 
            while ((j < i) && (i%j != 0))//j������,ѭ����i,һ��j��������i���� 
                 j++;
            if (j == i){//���ѭ������ʱi=j,˵��i��һ������ 
                  str[k]=i;
                  k++;
            }
      }
      return k;//��������(������)���� 
}
