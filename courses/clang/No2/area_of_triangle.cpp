//9.�������������߱߳�,������
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

main()
{
    float a, b, c, s, area;
    
    printf ("���������߱߳�:");
    scanf ("%f%f%f", &a, &b, &c);
    
    if ((a >= b + c) || (c >= a + b) || (b >= a + c))
        printf ("�߳��д���,�鲻��������");
    else
        {
        s = (a + b + c)/2;
        area = sqrt (s*(s-a)*(s-b)*(s-c));
        printf ("�����ε����Ϊ:%f", area);       
        } 
    
    system ("pause");
    return 0;
} 
