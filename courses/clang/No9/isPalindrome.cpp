/*
  Name: 9.回文字符串 
  Copyright: Free 
  Author: Joker Lee      
  Date: 07-12-04 19:56
  Description: 判断一个字符串是否是回文字符串 
  递归思想：先判断字符串收尾元素是否相同，去掉收尾，递归 
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
	
	printf ("请输入待判断的字符串：");
	gets(string);//读入 
	length = strlen(string);//得到字符串长度 
	
	if (_isPalindrome(string, length, 0))//原字符串、长度、判断起始位置 
		printf ("该字符串是回文字符串\n");
	else
	      printf ("该字符串不是回文字符串\n"); NULL;

	system("pause");
	return 0;
}

int _isPalindrome(char* str, int len, int start)
{
	if (start!=len/2){
            if (str[start]==str[len-start-1])//若收尾相同，且没有达到中间元素 
                  //若递归到中间元素，则为回文字符串 
                  return _isPalindrome(str, len, start+1);//起始位置后移，递归                   
            else return 0;
      }
      else if (start==len/2) return 1;
      else return 0;//未达到中间位置就中断，则表明不是回文字符串 

}
