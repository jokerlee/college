/*
  Name: 3.找对手 
  Copyright: Free 
  Author: Joker Lee 
  Date: 04/11/07 14:04
  Description: ABC与XYZ比赛,找出所有组合,满足A不与X比赛,C不与XZ比赛(穷举法)
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char i,j,k;//i是A的对手，j是B的对手，k是C的对手	
	int l = 1;//l用于计算本次是第几个方案		
	int flag;//储存配对要求的条件，方便修改 
	 
	for(i = 'X';i <= 'Z';i++) { //为A找对手 
		for(j = 'X';j <= 'Z'; j++){//为B找对手 
			for(k = 'X';k <= 'Z';k++){ //为C找对手
				if(i!= j && i!=k && j!=k){ //为A、B、C对手各不相同时，打印 
					flag = (i!='X' && k!='X'&& k!='Z');
					if(flag != 0){
						printf("第%d种组合是:\n",l);
						printf("A与%c比赛\n",i);
						printf("B与%c比赛\n",j);
						printf("C与%c比赛\n",k);
						l++;//组合数计数器 
					}
				}
			}
		} 
	}

	system ("pause");	
	return 0;

}
