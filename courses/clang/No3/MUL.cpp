#include <stdio.h> 
#include <stdlib.h> 
main() 
{ 
    int i=1, j=1, n=0; 
    
    printf ("Please input N(N>0):");
    scanf ("%d", &n);
    
    while(i <= n) //����ѭ��1��9
    { 
        printf("%d*%d=%d, ", i, j, i*j); //���i*j=��
        
        if(i == j) //���i=j�ͻ�����
        { 
            ++i; 
            j = 0; 
            printf("\n"); 
        }
         
    j=1; 
    } 
    
    system ("pause");
    return 0;
}
