/*
  Name: 
  Copyright: 打印菱形 
  Author: 
  Date: 26-10-04 19:07
  Description: 
*/
#include<stdio.h>
#include <stdlib.h> 

main()
{
    int a, i, j, k, flag = 0;
    char ch;
     
    printf("输入一个大于1小于19的奇数"); /*输入数据*/
    scanf("%d",&i);
    
    while(i > 19 || i < 1 || i%2 == 0)/*判断数据是否正确*/
    {
        printf("数据错误请重新输入\n");
        scanf("%d",&i);
    }
    
    k = (i+1)/2;                       /*确定中间位置*/
    
    for(j = 0;j != -1;flag == 1?j--:j++)/*偏移值*/
    {
        if(j == k-1)
            flag = 1;                  /*判断是否过中间行*/
            
        for(a = 1;a <= i;a++)          /*打印一列*/
            if(a >= k-j && a <= k+j)    /*判断是否在打印范围内*/
                printf("* ");
            else
                printf("  ");
                
        printf("\n");                 /*换行*/
    }    
    
    printf("输入q或Q结束程序\n");
    while((ch=getchar()) != 'q' && ch != 'Q');/*结束*/
    return 0;
}
