/*
  Name:13.ǧ��λ 
  Copyright: free 
  Author: Joker Lee 
  Date: 31/10/06 21:40
  Description:  ����������Ӹ�λ��ÿ��λ֮���һ������ 
*/
#include <stdio.h> 
#include <stdlib.h> 

int main()
{
      int  div=1;//����,���ڽ�������λ��λ�طֿ� 
	int i=0;//�������ֵ�λ�� 
	int j=0, k = 0,;
	int result;//result���ڴ����������λ 
      int num, tempnum;//tempnum���ڼ���λ�� 
      
      printf ("n=");
      scanf ("%d", &num);
      
      tempnum = num;
      while (tempnum/10){//��ѭ���������ֵ�λ��������i 
            i++;
            tempnum/=10;
      }
                  
      while (j < i-i%3){//��ʼ����һ������,��һ��8λ��,��һ������Ϊ 1e6 
            div *= 10;
            j++;
      }      
      
      while (div > 0){
            result = num/div;
            printf ("%d", temp);
            if (num > 10000)//ʡȥ��λ��Ķ��� 
                  printf (", ");   
            num %= div;//ȥ���Ѿ���ӡ�Ĳ��� 
            div /= 1000;
      }
      
      system ("pause");
      return 0;
}
