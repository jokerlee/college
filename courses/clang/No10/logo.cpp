#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#define N 50

void _printTips();
void _straight(int [N][N], int*, int*, int, int, int);
void _printResult(const int [N][N], int);
int _isOut(int, int);
void _erase(int[N][N], int);

int main(int argc, char** argv)
{
	int map[N][N]={0};
	int cmd, draw=0, dir=0;
	int x=49, y=0;
	
	_printTips();
	do{
		printf ("cmd��");
		fflush(stdin);
		scanf ("%d,", &cmd);
		switch (cmd){
                  case 0: _erase(map, N); break;
			case 1: draw=0; break;//����״̬
			case 2: draw=1; break;
			case 3: dir=(++dir)%4; break;//��ת
			case 4: dir=(dir+3)%4; break;//��ת
			case 5:{//ǰ��
				scanf ("%d", &cmd);
				_straight(map, &x, &y, dir, cmd, draw);
				break;
			}
			case 6: _printResult(map, N); break;//��ӡ
                  case 7: printf ("��ǰ״̬������%d; λ��(%d,%d); ����״̬:%d\n", dir, x, y, draw); break;
                  case 8: {
				system("cls");
				_printTips();
				break;
			}
			case 9: break;//�˳�
			default:{
				printf ("Invalid command! Please input the valid command.\n");
				break;
			}
		}
	}while (cmd != 9);
	
	system("pause");
	return 0;
}
void _printTips()
{
	printf ("Produced by Joker Lee. 1:00/Nov/11/2008\n");
	printf ("command    0      1       2        3       4   �� 5 ,x ��  6   �� 7     8     9   \n");
	printf ("actions  �廭�� �ʳ���  �ʳ���  ��ת��  ��ת�䡡 ��ǰ�ߡ���ӡ   ״̬  ����  ���� \n\n");

	printf ("����0�� 1�� 2�� 3��; ����״̬:0����,1����\n");
}
void _straight(int sMap[N][N], int* x, int* y, int dir, int steps, int isDraw)
{
	int i=0, x1, y1;
	int direct[8]={-1,0,0,1,1,0,0,-1};
	
	x1 = direct[2*dir];
	y1 = direct[2*dir+1];
	if (!_isOut(*x+steps*x1, *y+steps*y1)){
		for (i=0; i<steps; i++){
			sMap [*x+x1] [*y+y1] = isDraw;
			*x += x1;
            	*y += y1;
		}
	}
      else
		printf ("Out of bound!\n");
}

int _isOut(int x, int y)
{
	return (x<N && y<N && x>=0 && y>=0)?0:1;
}

void _printResult(const int map[N][N], int max)
{
	int i=0, j=0, k=0;
	for (k=0; k<max+2; k++)
		printf ("-");
 	printf("\n");
	for (i=0; i<max; i++){
		printf ("|");
		for (j=0; j<max; j++){
			if (map[i][j]==1)
			      printf ("#");
			else
			      printf (" ");
			if (j==max-1)
			      printf ("|\n");

		}
	}
	for (k=0; k<max+2; k++)
		printf ("-");
  	printf("\n");
}
void _erase(int map[N][N], int max)
{
	int i,j;
	for (i=0; i<max; i++)
		for (j=0; j<max; j++)
			map[i][j]=0;
}
