/*
  Name: 5.������תʮ����(֧��С��) 
  Copyright: Free 
  Author: Joker Lee 
  Date: 04/11/07 14:06
  Description: ����һ����������,һ��һ�����벢�����һ������,��¼С����λ,
  		   �ٽ�ÿһλ����Ȩ�����,�õ�ʮ������ 
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	long int bin = 0;//����ȥ��С����Ķ������� 
	int i=0, j=0;//i����С����ǰ�ĳ���,j�����ܳ��� 
	int flag;//��ʾ�Ƿ��Ѿ�ȡ��С����ı��  
	int div=1;//divΪ����ʱ�õĳ���
	float  p=1;//��ǰ��������λ��Ȩֵ 
	float  dec=0; //Ϊ�������10������ 
	char n;
	
	printf ("������һ����������(��#����)��");
	n = getchar();
	
	if (n != ' '){//�ų���ǰ�ո� ���� 
		while (n != '#'){//����#�Ŵ������ 
			if (n == '1')
				bin = bin*10 + 1;
			else if (n == '0')
				bin = bin*10;	

			if (n== '.')
				flag = 1;//һ��ȡ��С����,���Ϊ1 
			if (flag != 1)
				i++;//����С����ǰλ�� 
						
			if (n != '.')
				j++;//��¼���������������� 
			n = getchar();
					
		}
	}	
	for (; i>1; i--)//��ʼ�����λȨֵ 
		p*=2;
	for (; j>1; j--)//��ʼ�����λ�ĳ��� 
		div *= 10;
		
	while (div > 1){
		while (bin/div == 0){//���������м��"0",�����λΪ��,���ʱbin/div=0 
			div /= 10;
			p /= 2;
		}
		dec += bin/div*p;
		
		bin %= div;//��ȥ���λ 
		div /= 10;
		p /= 2;
	}
	
	printf ("%f", dec);	
	system ("pause");
	return 0;	
	
}
