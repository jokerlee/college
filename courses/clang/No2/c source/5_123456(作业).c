//5.����һ����,����ÿλ�𿪴�ӡ 

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
main()
{
      long num, a, counter = 0;
      
      printf ("Please input an int number:");
      scanf ("%d", &num);
      
      a = num;
	  while (a /=10){//��ѭ������ȷ������λ��
		  counter++;}
		  

	  printf ("The result is: ");
	  counter = (float)pow(10,counter);//ѭ��ǰ��ʼ������
      while (counter/10>0)//��ѭ�����ڴ�ӡÿһλ
          {
		  printf ("%l ", num/counter);
          num -= (num/counter*counter);//��ӡ������ֵ���λȥ��
		  counter/=10;
          }
      
      printf ("%l" , num);
      
         
      system ("pause");
      return 0;
      }
