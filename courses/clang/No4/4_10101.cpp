/*
  Name: 4.������ת�� 
  Copyright:  Free 
  Author: Joker Lee 
  Date: 31/10/07 11:28
  Description: ������Ķ�������ת����10����
  �㷨������������������Ķ�����������һ���ַ������飬������ĩβ�����ȡ�ַ�
        ����ת����ʽÿλ����Ȩֵ������һ����ֵ��ÿѭ��һ��Ȩֵ*2 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char num[128];
	int p=0, i=1, n=1;//nΪ��ǰλ��Ȩ 
	
	printf ("������һ������������");
	scanf ("%s", num);
	
	i = strlen(num);//��ö�λ���ĳ���,�Կ���ѭ������ 
	while (i>=0){
		if (num[i-1] == '1')//�ַ�������ĩλΪ��ֹ��null,���Դӵ����ڶ�λ��ʼ 
			p += 1*n;//�������ܺ� 
		n *= 2;
		i --;
	}
	
	printf ("��Ӧ��ʮ������Ϊ��%d", p);
	system ("pause");
	return 0;
}
