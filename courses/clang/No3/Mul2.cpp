#include <stdio.h> 
#include <stdlib.h> 

main() 
{ 
    int i,j; 

    for(i=1;i<=9;i++) //进行行循环,循环9次打印9行 
    { 
        printf(" "); 
        
        for(j=1;j<=9;j++)//进行列循环,打印每一列的9个式子 
            printf("%1d×%1d=%2d ",i,j,i*j); 
            
        printf(" \n");  
    }
    
    system ("pause");
    return 0;
}
