//9.输入三角形三边边长,输出面积
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

main()
{
    float a, b, c, s, area;
    
    printf ("请输入三边边长:");
    scanf ("%f%f%f", &a, &b, &c);
    
    if ((a >= b + c) || (c >= a + b) || (b >= a + c))
        printf ("边长有错误,组不成三角形");
    else
        {
        s = (a + b + c)/2;
        area = sqrt (s*(s-a)*(s-b)*(s-c));
        printf ("三角形的面积为:%f", area);       
        } 
    
    system ("pause");
    return 0;
} 
