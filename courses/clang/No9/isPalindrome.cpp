/*
  Name: 9.�����ַ��� 
  Copyright: Free 
  Author: Joker Lee      
  Date: 07-12-04 19:56
  Description: �ж�һ���ַ����Ƿ��ǻ����ַ��� 
  �ݹ�˼�룺���ж��ַ�����βԪ���Ƿ���ͬ��ȥ����β���ݹ� 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024 

int _isPalindrome(char*, int, int);
int main(int argc, char* argv[])
{
	char string[SIZE];
	int length;
	
	printf ("��������жϵ��ַ�����");
	gets(string);//���� 
	length = strlen(string);//�õ��ַ������� 
	
	if (_isPalindrome(string, length, 0))//ԭ�ַ��������ȡ��ж���ʼλ�� 
		printf ("���ַ����ǻ����ַ���\n");
	else
	      printf ("���ַ������ǻ����ַ���\n"); NULL;

	system("pause");
	return 0;
}

int _isPalindrome(char* str, int len, int start)
{
	if (start!=len/2){
            if (str[start]==str[len-start-1])//����β��ͬ����û�дﵽ�м�Ԫ�� 
                  //���ݹ鵽�м�Ԫ�أ���Ϊ�����ַ��� 
                  return _isPalindrome(str, len, start+1);//��ʼλ�ú��ƣ��ݹ�                   
            else return 0;
      }
      else if (start==len/2) return 1;
      else return 0;//δ�ﵽ�м�λ�þ��жϣ���������ǻ����ַ��� 

}
