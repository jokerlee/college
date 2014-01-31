//4.输入一个四位数, 分别将每位数输出 
#include<stdlib.h> 
#include<stdio.h>

main()
{
    int num, i = 0, result, counter = 1000; 
    
    printf ("Please input four digits:");
    scanf ("%d", &num);                  
    
    printf ("The result is:");
    
    for (i = 4; i -- ; counter /= 10)
        {printf ("%d ", num / counter);
        num -= counter*(num/counter);}
    
    system ("pause");
    return 0;
}
