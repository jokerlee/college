#include <stdio.h> 
#include <stdlib.h> 
main() 
{ 
    int i=1, j=1, n=0; 
    
    printf ("Please input N(N>0):");
    scanf ("%d", &n);
    
    while(i <= n) //行上循环1到9
    { 
        printf("%d*%d=%d, ", i, j, i*j); //输出i*j=？
        
        if(i == j) //如果i=j就换行了
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
