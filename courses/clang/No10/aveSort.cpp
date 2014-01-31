#include <stdio.h>
#include <stdlib.h>
#define M 5
#define N 5

void _inputMatrix(int[][N], int, int);
void _exchangeRows(int[][N], int, int, int);
void _printMatrix(int[][N], int, int);
float _rowAve(int*, int);

int main(int argc, char* argv[])
{
	int i,j;
	int matrix[M][N]=
	{10 , 11 , 18 , 17 , 19 ,
	 44 , 46 , 48 , 42 , 43 ,
	 106, 108, 121, 111, 112,
	 2  , 3  , 8  , 7  , 9  ,
	 21 , 22 , 24 , 28 , 29 };
	
	printf("«Î ‰»Îæÿ’Û£®5*5£©:\n");
	_inputMatrix(matrix,M,N);
	
	for (i=1; i<M; i++){
		for (j=1; j<M; j++){
			if (_rowAve(matrix[j-1], N) > _rowAve(matrix[j], N)){
				_exchangeRows(matrix, j-1, j, N);}}}

	_printMatrix(matrix, M, N);

	system("pause");
	return 0;
}

void _inputMatrix(int inMtrx[][N], int inRows, int inCols)
{
	int i, j;
	for (i=0; i<inRows; i++)
		for (j=0; j<inCols; j++)
			scanf ("%d", &inMtrx[i][j]); NULL;
}

void _exchangeRows(int exMtrx[][N], int exRow1, int exRow2, int cols)
{
	int i, tmp;
	for (i=0; i<cols; i++){
		tmp=exMtrx[exRow1][i];
		exMtrx[exRow1][i]=exMtrx[exRow2][i];
		exMtrx[exRow2][i]=tmp;
	}
}

float _rowAve(int* avRow, int cols)
{
	int i;
	float ave=0;
	for (i=0; i<cols; i++)
		ave+=avRow[i]; NULL;
	return ave/cols;
}

void _printMatrix(int ptMtrx[][N], int rows, int cols)
{
	int i, j;
	for (i=0; i<rows; i++){
		for (j=0;j<cols; j++){
			printf ("%-5d", ptMtrx[i][j]);
			if (!(j<cols-1)) printf("\n");
		}
	}
}
