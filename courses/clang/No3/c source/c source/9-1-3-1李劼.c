//4.将输入的字母转换成其后面第三个字母 


#include <stdio.h> 
#include <stdlib.h> 

int main() 
{
      char a, isletter, isxyz;//a用于存储字符, flag为判断标记 
    
      fflush();
	
	  printf ("input the original word:\n");
      a = getchar();//读取刚刚存在键盘缓冲区的字符 
    
      printf ("the word after translation is:");
    
      isxyz = ((a >= 'x') && (a<='z')) || ((a >= 'X') && (a<='Z'));
      //上句判断是否为xyz和XYZ的特殊情况 
      isletter = ((a >= 65) && (a <= 90)) || ((a >= 97) && (a <= 122));
      //上句判断a是否为字母 
      while(isletter != 0){//循环条件为取出的字符是字母         
            if (isxyz == 1) 
                  printf ("%c", a-23);
            else
                  printf ("%c", a+3);
            
            a = getchar();
        
            isxyz = ((a >= 'x') && (a<='z')) || ((a >= 'X') && (a<='Z'));
            isletter = ((a >= 65) && (a <= 90)) || ((a >= 97) && (a <= 122));
      }    
    
      printf("\n");
    
      system ("pause");
      return 0;
}
/*由于采用do while循环无法实现打印 "the word after translation is:",所以只能
采用while,并在循环外提前进行判断 */
