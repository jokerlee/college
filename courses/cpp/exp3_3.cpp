/*
3��	��������
��дC++����������¹��ܣ�
��1��	������ʵ�־��󣬶���һ��������࣬���԰�����
 	�����С���� lines, rows���С�������ʾ����
 	�������������ָ�룬���ݾ����С��̬���루new����
��2��	������ķ���������
 	���캯���������Ǿ����С����Ҫ��̬���������������飻
 	������������Ҫ�ͷž��������ָ�룻
 	�������캯������Ҫ����͸������飻
 	���룬���Դ�cin���������Ԫ�أ�
 	������������ʽ�������cout��
 	������ӵĺ�����ʵ������������ӵĹ���,�����������һ�������࣬����������С��ͬ��
 	��������ĺ�����ʵ��������������Ĺ���,�����������һ�������࣬����������С��ͬ��
��3��	������������A1��A2��A3��
��4��	��ʼ��A1��A2��
��5��	���㲢���A3 = A1��A2��A3=A1��A2��
��6��	��new��̬��������������Ķ���pA1��pA1��pA3��
��7��	��ʼ��pA1��pA2��
��8��	���㲢���pA3=pA1��pA2��pA3=pA1��pA2��
��9��	�ͷ�pA1��pA1��pA3��
*/ 

#include <iostream>
#include <iomanip>

using namespace std;

class Matrix
{
private:
	int row;
	int col;
	int **data;
public:
	Matrix( int r=0, int c=0 );
	Matrix( const Matrix& m );//�������캯�� 
	~Matrix();
	void ouput()const;
	void initial();
	Matrix& add( Matrix& )const;//������� 
	Matrix& minus( Matrix& )const;//�������
};


Matrix::Matrix( int r, int c )
{
    row = r;
    col = c;
    data = new int*[r];
    data[0] = new int[r*c];
    for( int i=1; i<r; i++ )
        data[i] = data[i-1]+c;
}

Matrix::Matrix( const Matrix& m )
{
	row = m.row;
	col = m.col;
	data = new int*[row];
	data[0] = new int[row*col];
	for ( int i=1; i<row; i++ )
	    data[i] = data[i-1]+col;
	for ( int i=0; i<row; i++ )
	    for ( int j=0; j<col; j++ )
	        data[i][j] = m.data[i][j];
}

Matrix::~Matrix()
{
    delete [] data[0];
    delete [] data;
}

Matrix& Matrix::add( Matrix& m )const
{
	Matrix *ans = new Matrix( row, col );
	if ( row != m.row || col != m.col )
	{
		cout << "�����С��ͬ,�޷����" << endl;
		return  *ans;
	}
	for ( int i=0; i<row; i++ )
	    for ( int j=0; j<col; j++ )
	        (*ans).data[i][j] = data[i][j]+m.data[i][j];
    return *ans;
}

Matrix& Matrix::minus( Matrix& m )const
{
	Matrix *ans = new Matrix( row, col );
	if ( row != m.row || col != m.col )
	{
		cout << "�����С��ͬ,�޷����" << endl;
		return *ans;
	}
	for ( int i=0; i<row; i++ )
	    for ( int j=0; j<col; j++ )
	        (*ans).data[i][j] = data[i][j]-m.data[i][j];
     return *ans;

}

void Matrix::initial()
{
	cout << "��ʼ������" << row << "*" << col << ":" << endl;
	for ( int i=0; i<row; i++ )
	    for ( int j=0; j<col; j++ )
	        cin >> data[i][j];
}

void Matrix::ouput()const
{
	for ( int i=0; i<row; i++ )
	{
		for ( int j=0; j<col; j++ )
			cout << setw(4) << data[i][j];;
		cout << endl;
	}
}

int main()
{
	int r, c;
	cout << "����������С��" << endl;
	cin >> r >> c;

	Matrix A1( r,c ), A2( r,c );

	A1.initial();
	A2.initial();
	
	Matrix A3;
    A3 = A1.add( A2 );
	cout << "����A3=A1+A2" << endl;
	A3.ouput();
	A3 = A1.minus( A2 );
	cout << "����A3=A1-A2" << endl;
	A3.ouput();

	system( "pause" );
	return 0;
}
