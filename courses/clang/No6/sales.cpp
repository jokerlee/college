#include <stdio.h>
#include <stdlib.h>
#define PRICE1 2.98
#define PRICE2 4.50
#define PRICE3 9.98
#define PRICE4 4.49
#define PRICE5 6.87

int main()
{
	int id=0, day, num; 
	float sum=0;
	
	printf ("��������һֱ����������������������Ʒ�ţ���������");
	printf ("��Ʒ��Ϊ-1����������\n");
	
	for (day=1; day<6; day++){
		printf ("��%d�������:\n", day); 
		do{
			scanf ("%d,%d", &id, &num);
			switch (id){
				case 1:sum += num*PRICE1;break;
				case 2:sum += num*PRICE2;break;
				case 3:sum += num*PRICE3;break;
				case 4:sum += num*PRICE4;break;
				case 5:sum += num*PRICE5;break;
				default:;break;
			}
		}while (id != -1);
	}
	printf ("���ܵ������ܶ�Ϊ��%f", sum);
	
	system ("pause");
	return 0;		 
}
