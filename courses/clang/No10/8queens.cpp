#include "stdio.h"
#include "stdlib.h"
#define DEBUG 0
#define N 10

int n=0;

void _locQueen(int [N][N], int, int);
void _occupy(int [N][N], int, int, int);
void _copyBoard(const int [N][N], int [N][N], int);
void _printBoard(const int [N][N], int);

int main(int argc, char* argv[])
{
	int cheBoard[N][N]={0};
	
	_locQueen(cheBoard, 0, N);
      
	system("pause");
	return 0;
}

void _locQueen(int board[N][N], int row, int max)
{
	int col,i=0;
	int tmp[N][N];
	

	for (col=0; col<max; col++){
		if (board[row][col]==0){
			_copyBoard(board, tmp, max);
			_occupy(board, row, col, max);
                  _locQueen(board, row+1, max);
                  if (row == max-1){
				printf ("\n      ---布局%d---\n", ++n);
				_printBoard(board, max);
				system("pause");
			}
                  _copyBoard(tmp, board, max);//恢复上一次占位前的状态
		}
	}
}

void _occupy(int board[N][N], int ocRow, int ocCol, int max)
{
	int i;
	//占行、列
	for (i=0; i<max; i++){
		--board[ocRow][i];
		--board[i][ocCol];
	}
	//占位主对角线
	for (i=1; ocRow-i>=0 && ocCol-i>=0; i++)
		--board[ocRow-i][ocCol-i];
	for (i=1; ocRow+i<max && ocCol+i<max; i++)
		--board[ocRow+i][ocCol+i];
      //占位副对角线
	for (i=1; ocRow+i<max && ocCol-i>=0; i++)
		--board[ocRow+i][ocCol-i];
	for (i=1; ocRow-i>=0 && ocCol+i<max; i++)
		--board[ocRow-i][ocCol+i];

	board[ocRow][ocCol]=1;
	#if DEBUG
		_printBoard(board,max);
      	system("pause");
	#endif
}

void _copyBoard(const int board[N][N], int tmp[N][N], int max)
{
	int i, j;

	for (i=0; i<max; i++)
	      for (j=0; j<max; j++)
	            tmp[i][j]=board[i][j];
	      
}
void _printBoard(const int board[N][N], int max){
	int i,j=0;
	
	for (i=0; i<max; i++){
		if (j==max)		printf("\n");
		for (j=0; j<max; j++){
			if (board[i][j]==1)
				printf (" ●");
			else
				printf (" □");
		}
	}
	printf ("\n");
}
