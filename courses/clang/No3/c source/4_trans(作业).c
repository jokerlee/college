//4.���������ĸת����������������ĸ 


#include <stdio.h> 
#include <stdlib.h> 

int main() 
{
      char a, isletter, isxyz;//a���ڴ洢�ַ�, flagΪ�жϱ�� 
    
      fflush();
	
	  printf ("input the original word:\n");
      a = getchar();//��ȡ�ոմ��ڼ��̻��������ַ� 
    
      printf ("the word after translation is:");
    
      isxyz = ((a >= 'x') && (a<='z')) || ((a >= 'X') && (a<='Z'));
      //�Ͼ��ж��Ƿ�Ϊxyz��XYZ��������� 
      isletter = ((a >= 65) && (a <= 90)) || ((a >= 97) && (a <= 122));
      //�Ͼ��ж�a�Ƿ�Ϊ��ĸ 
      while(isletter != 0){//ѭ������Ϊȡ�����ַ�����ĸ         
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
/*���ڲ���do whileѭ���޷�ʵ�ִ�ӡ "the word after translation is:",����ֻ��
����while,����ѭ������ǰ�����ж� */
