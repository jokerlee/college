#include <stdio.h> 
#include <stdlib.h> 

main() 
{ 
    int i,j; 

    for(i=1;i<=9;i++) //������ѭ��,ѭ��9�δ�ӡ9�� 
    { 
        printf(" "); 
        
        for(j=1;j<=9;j++)//������ѭ��,��ӡÿһ�е�9��ʽ�� 
            printf("%1d��%1d=%2d ",i,j,i*j); 
            
        printf(" \n");  
    }
    
    system ("pause");
    return 0;
}
