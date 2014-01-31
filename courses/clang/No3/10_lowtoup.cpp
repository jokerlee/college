//输入一个字符串以#结尾，将其中的小写字母转换成大写，并输出 
#include <stdio.h> 
#include <stdlib.h> 
#define N = 128

int main() 
{ 
	char str [128];
	int i = 0;
	
    printf ("Please input a String(end with \"#\"):\n");
	scanf ("%s", str);

	while(str[i] != '#')
	{    
        if ((str[i] >= 'a') && (str[i] <= 'z'))
            str[i] -=32;
        i++;
    }
    
    str[i] = 0;
    
	printf ("The result is:\n%s", str);

	system("pause");
	return 0;
}
