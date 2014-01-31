/*
  Name: 4.食量问题 
  Copyright: Free 
  Author: Joker Lee 
  Date: 04/11/07 14:06
  Description: 
*/
#include <stdio.h>
#include <stdlib.h>

int max(int,int,int);//求三个数中的最大值 
int min(int,int,int);//求三个数中的最小值
int main()
{
	int flag[16];//储存 A,B,C三人说真话的数目 
	int flagMax, flagMin, flagEqual;//作用见下 
	int a, b, c;//a,b,c分循环A,B,C食量,0代表最小,1是中间值,2最大 
	
	for (a=0; a<3; a++){
		for (b=0; b<3; b++){
			for (c=0; c<3; c++){
				if (a != b && b != c && a != c){//a,b,c 
					flag[a] = (a<b) + (a==c);
					flag[b] = (b<a) + (a>c); 
					flag[c] = (c>b) + (b>a);									
					flagMax = (max(a,b,c) == min(flag[a],flag[b],flag[c]));
					//判断说食量最大的是否是说真话最多的 
					flagMin = (min(a,b,c) == max(flag[a],flag[b],flag[c]));
					//判断说食量最小的是否是说真话最少的 
					flagEqual = ((flag[a]!= flag[b])&&(flag[b]!=flag[c])&&(flag[a]!=flag[c]));
					//判断三人说的真话是否不相等 
					if (flagMax && flagMin && flagEqual > 0){//若以上三个条件都成立,则打印 
						printf("饭量最大的是:%c\n", max(a,b,c));					
						printf("饭量最小的是:%c\n", min(a,b,c));
					}
				}
			}
		}
	}		
	system ("pause");
	return 0;			

	
}

int max(int a,int b,int c)
{
	char max;
	
	if (a>b && a>c)
		max = 'A';
	else if (b>a && b>c)
		max = 'B';
	else
		max = 'C';  
	return max;
}	

int min(int a, int b, int c)
{
	char min;
	
	if (a<b && a<c)
		min = 'A';
	else if (b<a && b<c)
		min = 'B';
	else
		min = 'C';  
	return min;
}
