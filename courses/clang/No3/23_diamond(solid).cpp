//��ӡһ��7�еĿ������� 

#include <stdio.h> 
#include <stdlib.h> 
#define N 5

int main()
{
    int c=0, i=0, j=0;//c��j��Ϊ����ѭ�����м���� ,j���ڴ�����к�ĵݼ� 
    
      
    for (i = 1; i < 2*N ;i ++) //��ѭ����ӡÿһ�� 
    {    
        j = i;
        if (j > N) //������к�ĵݼ� 
            j = 2*N - j;
        
        for (c = N - j + 1; c > 0; c--)//��ѭ����ӡÿ��*ǰ�Ŀո� 
            printf(" ");
        

        for (c = 0; c < 2*j - 3; c ++) //��ѭ����ӡÿ��*
            printf("*");
        
        printf("\n");  
    } 
    
    
    system ("pause");
    return 0;

} 
