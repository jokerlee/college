
/*
4��	�ο���ʵ�������о���������������������ͣ���ʵ�־���ļӼ���
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
	int rows()const;
	int cols()const;
	void ouput()const;
	void initial();
	Matrix& operator+( const Matrix& m )const;
	Matrix& operator-( const Matrix& m )const;
};


Matrix::Matrix( int r, int c )
{
    row = r;
    col = c;
    data = new int*[r];
    data[0] = new int[r*c];
    for( int i=1; i<r; i++ )
        data[i] = data[i-1]+c;
    cout << "Constructor" << endl;
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
    cout << "Destructor" << endl;
}

Matrix& Matrix::operator+( const Matrix& m )const
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

Matrix& Matrix::operator-( const Matrix& m )const
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


int Matrix::rows()const
{
	return row;
}

int Matrix::cols()const
{
	return col;
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
{
	int r, c;
	cout << "����������С��" << endl;
	cin >> r >> c;

	Matrix A1( r,c ), A2( r,c );

	A1.initial();
	A2.initial();
	
	Matrix A3( A1+A2 );
	cout << "����A3=A1+A2" << endl;
	A3.ouput();
	
	A3 = A1-A2;
	cout << "����A3=A1-A2" << endl;
	A3.ouput();
}
	system( "pause" );
	return 0;
}
