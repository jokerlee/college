/*
1��	����һ��
��дC++����������¹��ܣ�
��1��	�ٶ������СΪ4��5�����������ʾ����
��2��	��������ʼ�����������Դ�cin���������Ԫ�أ�
��3��	�����������������������ʽ�������cout��
��4��	���������ӵĺ�����ʵ������������ӵĹ���,�����������һ�������У�
��5��	�����������ĺ�����ʵ��������������Ĺ���,�����������һ�������У�
��6��	������������A1��A2��A3��
��7��	��ʼ��A1��A2��
��8��	���㲢�����A3 = A1��A2��A3 = A1��A2��
*/

#include <iostream>
#include <iomanip>
using namespace std;

int const M = 4;
int const N = 5;

//�����ʼ������ 
void initial( int matrix[M][N] )
{
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
			cin >> matrix[i][j];
}

//����������� 
void output( int matrix[M][N] )
{
	for ( int i=0; i<M; i++ )
	{
		for ( int j=0; j<N; j++ )
			cout << setw(5) << matrix[i][j];
		cout << endl;
	}
}

//����ӷ����� 
void matrix_add( int mx1[M][N], int mx2[M][N], int mx[M][N] )
{
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
			mx[i][j] = mx1[i][j] + mx2[i][j];
}
 
//����������� 
void matrix_minus( int mx1[M][N], int mx2[M][N], int mx[M][N] )
{
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
			mx[i][j] = mx1[i][j] - mx2[i][j];
}

int main()
{
	int A1[M][N], A2[M][N], A3[M][N];
    cout << "���������1(4*5):" << endl;
	initial( A1 );
    cout << "���������2(4*5):" << endl;
	initial( A2 );
	matrix_add( A1, A2, A3 );
	cout << "����A3=A1+A2��" << endl;
	output( A3 );
	matrix_minus( A1, A2, A3 );
	cout << "����A3=A1-A2��" << endl;
	output( A3 );

	system( "pause" );
	return 0;

}
