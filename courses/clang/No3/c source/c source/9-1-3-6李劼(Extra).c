//10.����һ���ַ�����#��β�������е�Сд��ĸת���ɴ�д������� 


#include <stdio.h> 
#include <stdlib.h> ����һ���ַ�����#��β�������е�Сд��ĸת���ɴ�д�������
#define N = 128

int main() 
{ 
	  char str [128];
	  int i = 0;
	
      printf ("Please input a String(end with \"#\"):\n");
	  scanf ("%s", str);

	  while(str[i] != '#')//��ȡ��"#"ʱ����ѭ�� 
	  {    
            if ((str[i] >= 'a') && (str[i] <= 'z'))//����Сд��ĸ,ת���ɴ�д 
                  str[i] -=32;
            i++;
      }
    
      str[i] = 0;//ȥ���ַ���ĩβ��"#" 
    
	  printf ("The result is:\n%s", str);

	  system("pause");
	  return 0;
}
