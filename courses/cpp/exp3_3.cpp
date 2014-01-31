/*
3、	矩阵（三）
编写C++程序完成以下功能：
（1）	用类来实现矩阵，定义一个矩阵的类，属性包括：
 	矩阵大小，用 lines, rows（行、列来表示）；
 	存贮矩阵的数组指针，根据矩阵大小动态申请（new）。
（2）	矩阵类的方法包括：
 	构造函数，参数是矩阵大小，需要动态申请存贮矩阵的数组；
 	析构函数，需要释放矩阵的数组指针；
 	拷贝构造函数，需要申请和复制数组；
 	输入，可以从cin中输入矩阵元素；
 	输出，将矩阵格式化输出到cout；
 	矩阵相加的函数，实现两个矩阵相加的功能,结果保存在另一个矩阵类，但必须矩阵大小相同；
 	矩阵相减的函数，实现两个矩阵相减的功能,结果保存在另一个矩阵类，但必须矩阵大小相同。
（3）	定义三个矩阵：A1、A2、A3；
（4）	初始化A1、A2；
（5）	计算并输出A3 = A1加A2，A3=A1减A2；
（6）	用new动态创建三个矩阵类的对象：pA1、pA1、pA3；
（7）	初始化pA1、pA2；
（8）	计算并输出pA3=pA1加pA2，pA3=pA1减pA2；
（9）	释放pA1、pA1、pA3。
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
	Matrix( const Matrix& m );//拷贝构造函数 
	~Matrix();
	void ouput()const;
	void initial();
	Matrix& add( Matrix& )const;//矩阵相加 
	Matrix& minus( Matrix& )const;//矩阵相减
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
		cout << "矩阵大小不同,无法相加" << endl;
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
		cout << "矩阵大小不同,无法相减" << endl;
		return *ans;
	}
	for ( int i=0; i<row; i++ )
	    for ( int j=0; j<col; j++ )
	        (*ans).data[i][j] = data[i][j]-m.data[i][j];
     return *ans;

}

void Matrix::initial()
{
	cout << "初始化矩阵" << row << "*" << col << ":" << endl;
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
	cout << "请输入矩阵大小：" << endl;
	cin >> r >> c;

	Matrix A1( r,c ), A2( r,c );

	A1.initial();
	A2.initial();
	
	Matrix A3;
    A3 = A1.add( A2 );
	cout << "矩阵A3=A1+A2" << endl;
	A3.ouput();
	A3 = A1.minus( A2 );
	cout << "矩阵A3=A1-A2" << endl;
	A3.ouput();

	system( "pause" );
	return 0;
}
