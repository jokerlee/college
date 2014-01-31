/*
1、	矩阵（一）
编写C++程序完成以下功能：
（1）	假定矩阵大小为4×5（整型数组表示）；
（2）	定义矩阵初始化函数，可以从cin中输入矩阵元素；
（3）	定义矩阵输出函数，将矩阵格式化输出到cout；
（4）	定义矩阵相加的函数，实现两个矩阵相加的功能,结果保存在另一个矩阵中；
（5）	定义矩阵相减的函数，实现两个矩阵相减的功能,结果保存在另一个矩阵中；
（6）	定义三个矩阵：A1、A2、A3；
（7）	初始化A1、A2；
（8）	计算并输出：A3 = A1加A2，A3 = A1减A2。
*/

#include <iostream>
#include <iomanip>
using namespace std;

int const M = 4;
int const N = 5;

//矩阵初始化函数 
void initial( int matrix[M][N] )
{
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
			cin >> matrix[i][j];
}

//矩阵输出函数 
void output( int matrix[M][N] )
{
	for ( int i=0; i<M; i++ )
	{
		for ( int j=0; j<N; j++ )
			cout << setw(5) << matrix[i][j];
		cout << endl;
	}
}

//矩阵加法函数 
void matrix_add( int mx1[M][N], int mx2[M][N], int mx[M][N] )
{
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
			mx[i][j] = mx1[i][j] + mx2[i][j];
}
 
//矩阵减法函数 
void matrix_minus( int mx1[M][N], int mx2[M][N], int mx[M][N] )
{
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
			mx[i][j] = mx1[i][j] - mx2[i][j];
}

int main()
{
	int A1[M][N], A2[M][N], A3[M][N];
    cout << "请输入矩阵1(4*5):" << endl;
	initial( A1 );
    cout << "请输入矩阵2(4*5):" << endl;
	initial( A2 );
	matrix_add( A1, A2, A3 );
	cout << "矩阵A3=A1+A2：" << endl;
	output( A3 );
	matrix_minus( A1, A2, A3 );
	cout << "矩阵A3=A1-A2：" << endl;
	output( A3 );

	system( "pause" );
	return 0;

}
