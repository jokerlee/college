/*
  Name: 3.字符串中最长的单词 
  Copyright: Free 
  Author: Joker Lee 
  Date: 07-12-04 19:48
  Description: 找出字符串中最长的单词 ，字符串输入以#号结束 
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

int _isLetter(char);//判断一个字符是否为字母 
int main(int argc, char* argv[])
{
	int i=0, maxLoc=0, firstLtr=0, len=0, maxLen=0;
	// len储存当前单词的长度，maxLen为当前最长单词的长度， firstLtr为当前单词首字母位置
      //maxLoc为当前最长单词首字母位置 
      char str[SIZE];

	printf ("Please input the string('#'to end):\n");

	fflush(stdin);//清空键盘缓冲区 
	gets(str);//读入句子 

	for (i=0; str[i]!=0; i++){
  		if (!_isLetter(str[i])){//不是字母时 
			if (len>maxLen){//若当前单词长度大于最大长度 
				maxLen = len;//更新最大长度 
				maxLoc = firstLtr;//更新最长单词首字母位置 
			}
			firstLtr=i+1;//将单词首字母位置后移一位 
			len=0;//长度归零 
		}
		else len++;//是字母时长度+1 
	}

	printf ("The longest word is:");
	for (i=0; i<maxLen; i++)
		printf ("%c", str[maxLoc+i]); NULL;

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
