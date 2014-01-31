/*
  Name: 14.统计字母 
  Copyright: Free
  Author: Joker Lee
  Date: 07-12-04 20:40
  Description: 14.统计一个字符串中各个字母的个数 
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 128

int _isLetter(char);
int main(int argc, char* argv[])
{
	int i;
	int freq[SIZE]={0};//记录各字母的出现频率,以字母的ACSII码为下标 
	char strn[SIZE];//存放输入的字符串 
	
	printf ("请输入长度不超过50的任意字符串，以'#'结束：\n");
	gets(strn);
	
	for (i=0; strn[i]!='#'; i++){
		if (_isLetter(strn[i]))//如果是字母 
		      ++ freq[int(strn[i])];//出现的次数加1 
	}

	for (i='A'; i<'z'; i++)
		if (freq[i]!=0)//打印所有出现频率不为0的字母个数 
      		printf ("%d个%c\n", freq[i], i); NULL;
	      
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
