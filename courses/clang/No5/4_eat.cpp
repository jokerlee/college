/*
  Name: 4.ʳ������ 
  Copyright: Free 
  Author: Joker Lee 
  Date: 04/11/07 14:06
  Description: 
*/
#include <stdio.h>
#include <stdlib.h>

int max(int,int,int);//���������е����ֵ 
int min(int,int,int);//���������е���Сֵ
int main()
{
	int flag[16];//���� A,B,C����˵�滰����Ŀ 
	int flagMax, flagMin, flagEqual;//���ü��� 
	int a, b, c;//a,b,c��ѭ��A,B,Cʳ��,0������С,1���м�ֵ,2��� 
	
	for (a=0; a<3; a++){
		for (b=0; b<3; b++){
			for (c=0; c<3; c++){
				if (a != b && b != c && a != c){//a,b,c 
					flag[a] = (a<b) + (a==c);
					flag[b] = (b<a) + (a>c); 
					flag[c] = (c>b) + (b>a);									
					flagMax = (max(a,b,c) == min(flag[a],flag[b],flag[c]));
					//�ж�˵ʳ�������Ƿ���˵�滰���� 
					flagMin = (min(a,b,c) == max(flag[a],flag[b],flag[c]));
					//�ж�˵ʳ����С���Ƿ���˵�滰���ٵ� 
					flagEqual = ((flag[a]!= flag[b])&&(flag[b]!=flag[c])&&(flag[a]!=flag[c]));
					//�ж�����˵���滰�Ƿ���� 
					if (flagMax && flagMin && flagEqual > 0){//��������������������,���ӡ 
						printf("����������:%c\n", max(a,b,c));					
						printf("������С����:%c\n", min(a,b,c));
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
