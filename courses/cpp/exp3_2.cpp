/* 
2��	���󣨶���
��дC++����������¹��ܣ�
��1��	�ٶ������СΪ4��5�����ͣ���
��2��	����ռ����new��̬���룬������ָ���У�
��3��	��������ʼ�����������Դ�cin���������Ԫ�أ�
��4��	�����������������������ʽ�������cout��
��5��	���������ӵĺ�����ʵ������������ӵĹ���,�����������һ�������У�
��6��	�����������ĺ�����ʵ��������������Ĺ���,�����������һ�������У�
��7��	��̬������������A1��A2��A3��
��8��	��ʼ��A1��A2��
��9��	���㲢���A3 = A1��A2��A3 = A1��A2��
��10��	�ͷž���ռ䡣
*/ 

#include <iostream>
#include <iomanip>
using namespace std;

int const M = 4;
int const N = 5;

void initial( int matrix[M][N] )
{
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
			cin >> matrix[i][j];
}

void output( int matrix[M][N] )
{
	for ( int i=0; i<M; i++ )
	{
		for ( int j=0; j<N; j++ )
			cout << setw(4) << matrix[i][j];
		cout << endl;
	}
}

void matrix_add( int mx1[M][N], int mx2[M][N], int mx[M][N] )
{
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
			mx[i][j] = mx1[i][j] + mx2[i][j];
}

void matrix_minus( int mx1[M][N], int mx2[M][N], int mx[M][N] )
{
	for ( int i=0; i<M; i++ )
		for ( int j=0; j<N; j++ )
			mx[i][j] = mx1[i][j] - mx2[i][j];
}

int main()
{
	int(*A1)[N] = new int[M][N];//��̬�����ڴ� 
	int(*A2)[N] = new int[M][N];
	int(*A3)[N] = new int[M][N];
	
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

	delete []A1;//�ͷŶ��е��ڴ� 
	delete []A2;
	delete []A3;
	
	system( "pause" );
	return 0;

}
