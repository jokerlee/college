/*
  Name: ������
  Copyright: 
  Author: 
  Date: 21-11-07 19:52
  Description:��������Ϸ 
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
      int num;//����� 
      int guessN;//guessN��Ҳµ����� 
      int isright, flag;//��ȷ��Ǻͽ������ 

      do{
            srand(time(NULL));//��ʼ������ 
            num = rand()%1000+1;//����1~1000����� 
            printf ("I have a number between 1 and 1000.\nCan you guess my number?");
     
            isright=0;//����Ƿ�¶� 
            
            flag = 0;//��ʼ��������� 
            do{
                  scanf ("%d", &guessN);
                  //�ж��Ƿ�¶Բ��������� 
                  if (guessN > num)
                        printf ("Too high,try again.\n");
                  else if (guessN < num)
                        printf ("Too low,try again.\n");
                  else{
                        printf ("Excellent!You guess the number.\n");
                        isright = 1;//�������Ϊ�� 
                  }
            }while (isright!=1);
            
            printf ("Would you like to play again?(y or n):");
            fflush(stdin);//��ռ��̻�����,�������س� 
            scanf ("%c", &flag);
      }while (flag == 'y');
      
      system ("pause");
      return 0;

} 
