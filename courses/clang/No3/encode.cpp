#include <stdio.h> 
#include <stdlib.h> 
int main() 
{
    char a, flag1, flag2;//a���ڴ洢�ַ�, flagΪ�жϱ�� 
    
    //fflush();
	
	printf ("input the original word:\n");
    a = getchar();//��ȡ�ոմ��ڼ��̻��������ַ� 
    
    printf ("the word after translation is:");
    
    flag1 = ((a >= 'x') && (a<='z')) || ((a >= 'X') && (a<='Z'));
    //�Ͼ��ж��Ƿ�Ϊxyz��XYZ��������� 
    flag2 = ((a >= 65) && (a <= 90)) || ((a >= 97) && (a <= 122));
    //�Ͼ��ж�a�Ƿ�Ϊ��ĸ 
    while(flag2 != 0)//ѭ������Ϊȡ�����ַ�����ĸ 
    {    
        
        if (flag1 == 1) 
            printf ("%c", a-23);
        else
            printf ("%c", a+3);
            a = getchar();
        
        flag1 = ((a >= 'x') && (a<='z')) || ((a >= 'X') && (a<='Z'));
        flag2 = ((a >= 65) && (a <= 90)) || ((a >= 97) && (a <= 122));
    }    
    
    printf("\n");
    
    system ("pause");
    return 0;
}
/*���ڲ���do whileѭ���޷�ʵ�ִ�ӡ "the word after translation is:",����ֻ��
����while,����ѭ������ǰ�����ж� */
