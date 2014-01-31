//输入一个数,将其首位去掉并打印
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>

int main()
{
    unsigned long num;
    long i=1, j;
    
    printf ("w=");
    scanf ("%d", &num);
    
    j = pow(10,i);
    for (i = 1; num/j; i++)
        j *= 10;
    
    num = num%(j/10);
    
    printf ("output=%d", num);
    
    system("pause");
    return 0;
} 
