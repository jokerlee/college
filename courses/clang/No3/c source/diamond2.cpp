/*
  Name: 
  Copyright: ��ӡ���� 
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
     
    printf("����һ������1С��19������"); /*��������*/
    scanf("%d",&i);
    
    while(i > 19 || i < 1 || i%2 == 0)/*�ж������Ƿ���ȷ*/
    {
        printf("���ݴ�������������\n");
        scanf("%d",&i);
    }
    
    k = (i+1)/2;                       /*ȷ���м�λ��*/
    
    for(j = 0;j != -1;flag == 1?j--:j++)/*ƫ��ֵ*/
    {
        if(j == k-1)
            flag = 1;                  /*�ж��Ƿ���м���*/
            
        for(a = 1;a <= i;a++)          /*��ӡһ��*/
            if(a >= k-j && a <= k+j)    /*�ж��Ƿ��ڴ�ӡ��Χ��*/
                printf("* ");
            else
                printf("  ");
                
        printf("\n");                 /*����*/
    }    
    
    printf("����q��Q��������\n");
    while((ch=getchar()) != 'q' && ch != 'Q');/*����*/
    return 0;
}
