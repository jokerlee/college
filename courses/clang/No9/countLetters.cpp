/*
  Name: 14.ͳ����ĸ 
  Copyright: Free
  Author: Joker Lee
  Date: 07-12-04 20:40
  Description: 14.ͳ��һ���ַ����и�����ĸ�ĸ��� 
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 128

int _isLetter(char);
int main(int argc, char* argv[])
{
	int i;
	int freq[SIZE]={0};//��¼����ĸ�ĳ���Ƶ��,����ĸ��ACSII��Ϊ�±� 
	char strn[SIZE];//���������ַ��� 
	
	printf ("�����볤�Ȳ�����50�������ַ�������'#'������\n");
	gets(strn);
	
	for (i=0; strn[i]!='#'; i++){
		if (_isLetter(strn[i]))//�������ĸ 
		      ++ freq[int(strn[i])];//���ֵĴ�����1 
	}

	for (i='A'; i<'z'; i++)
		if (freq[i]!=0)//��ӡ���г���Ƶ�ʲ�Ϊ0����ĸ���� 
      		printf ("%d��%c\n", freq[i], i); NULL;
	      
	system ("pause");
	return 0;
}

int _isLetter(char a)
{
	if ((a>='A'&& a<='Z')||(a>='a' && a<='z'))
	      return 1;
	else
	      return 0;
}
