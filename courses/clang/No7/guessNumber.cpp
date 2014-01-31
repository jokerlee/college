/*
  Name: 猜数字
  Copyright: 
  Author: 
  Date: 21-11-07 19:52
  Description:猜数字游戏 
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
      int num;//随机数 
      int guessN;//guessN玩家猜的数字 
      int isright, flag;//正确标记和结束标记 

      do{
            srand(time(NULL));//初始化种子 
            num = rand()%1000+1;//产生1~1000随机数 
            printf ("I have a number between 1 and 1000.\nCan you guess my number?");
     
            isright=0;//标记是否猜对 
            
            flag = 0;//初始化结束标记 
            do{
                  scanf ("%d", &guessN);
                  //判断是否猜对并给出建议 
                  if (guessN > num)
                        printf ("Too high,try again.\n");
                  else if (guessN < num)
                        printf ("Too low,try again.\n");
                  else{
                        printf ("Excellent!You guess the number.\n");
                        isright = 1;//答对则标记为真 
                  }
            }while (isright!=1);
            
            printf ("Would you like to play again?(y or n):");
            fflush(stdin);//清空键盘缓冲区,避免读入回车 
            scanf ("%c", &flag);
      }while (flag == 'y');
      
      system ("pause");
      return 0;

} 
