//打印一个7行的空心菱形 

#include <stdio.h> 
#include <stdlib.h> 
#define N 5

int main()
{
    int c=0, i=0, j=0;//c与j均为控制循环的中间变量 ,j用于处理最长行后的递减 
    
      
    for (i = 1; i < 2*N ;i ++) //此循环打印每一行 
    {    
        j = i;
        if (j > N) //处理最长行后的递减 
            j = 2*N - j;
        
        for (c = N - j + 1; c > 0; c--)//此循环打印每行*前的空格 
            printf(" ");
        

        for (c = 0; c < 2*j - 3; c ++) //此循环打印每行*
            printf("*");
        
        printf("\n");  
    } 
    
    
    system ("pause");
    return 0;

} 
