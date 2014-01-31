//10.输入一个字符串以#结尾，将其中的小写字母转换成大写，并输出 


#include <stdio.h> 
#include <stdlib.h> 输入一个字符串以#结尾，将其中的小写字母转换成大写，并输出
#define N = 128

int main() 
{ 
	  char str [128];
	  int i = 0;
	
      printf ("Please input a String(end with \"#\"):\n");
	  scanf ("%s", str);

	  while(str[i] != '#')//当取到"#"时结束循环 
	  {    
            if ((str[i] >= 'a') && (str[i] <= 'z'))//若是小写字母,转化成大写 
                  str[i] -=32;
            i++;
      }
    
      str[i] = 0;//去除字符串末尾的"#" 
    
	  printf ("The result is:\n%s", str);

	  system("pause");
	  return 0;
}
