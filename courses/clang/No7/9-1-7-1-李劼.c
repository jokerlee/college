/*
  Name: ���ֽ���ת�� 
  Copyright: Free 
  Author: Joker Lee 
  Date: 21-11-07 17:49
  Description: ��10���Ƶ�����ת����������� 
*/

#include<stdio.h>
#include<stdlib.h>

void _convert(int ,int);
int main()
{
      int num, bit;
      
      printf ("������Ҫת���Ľ��ƺʹ�ת����ʮ������(����,ʮ������):\n");
      scanf ("%d,%d", &bit, &num);
      
      printf("ת����%d��������", bit);
      _convert(num, bit);//���ú���ת������ӡ 

      system("pause");
      return 0;
}
             
void _convert(int num, int n)
{
      int bitN=1;
      
      //�����λ��λֵ 
      while (num >= bitN)
          bitN=bitN*n;                                 
      bitN=bitN/n;                                        
     
      //ת�� 
      while (bitN != 0) {
            if (num/bitN < 10)
                  printf("%d", num/bitN);
            else//����16���� 
                  printf("%c", 'A'-10 + num/bitN); 
      
            num -= (num/bitN)*bitN;
            bitN = bitN/n;//��һλ��λֵ 
      }  
      printf ("\n");
}
