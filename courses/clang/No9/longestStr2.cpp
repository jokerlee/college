/*
  Name: 3.�ַ�������ĵ��� 
  Copyright: Free 
  Author: Joker Lee 
  Date: 07-12-04 19:48
  Description: �ҳ��ַ�������ĵ��� ���ַ���������#�Ž��� 
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

int _isLetter(char);//�ж�һ���ַ��Ƿ�Ϊ��ĸ 
int main(int argc, char* argv[])
{
	int i=0, maxLoc=0, firstLtr=0, len=0, maxLen=0;
	// len���浱ǰ���ʵĳ��ȣ�maxLenΪ��ǰ����ʵĳ��ȣ� firstLtrΪ��ǰ��������ĸλ��
      //maxLocΪ��ǰ���������ĸλ�� 
      char str[SIZE];

	printf ("Please input the string('#'to end):\n");

	fflush(stdin);//��ռ��̻����� 
	gets(str);//������� 

	for (i=0; str[i]!=0; i++){
  		if (!_isLetter(str[i])){//������ĸʱ 
			if (len>maxLen){//����ǰ���ʳ��ȴ�����󳤶� 
				maxLen = len;//������󳤶� 
				maxLoc = firstLtr;//�������������ĸλ�� 
			}
			firstLtr=i+1;//����������ĸλ�ú���һλ 
			len=0;//���ȹ��� 
		}
		else len++;//����ĸʱ����+1 
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
