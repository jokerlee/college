/*
3��	����ȡ��
��дC++����������¹��ܣ�ʹ�� enum����
��1��	�������� red, yellow, blue, white, black ������ɫ��������
��2��	һ�δӴ�����ȡ��3����ɫ��ͬ�����м���ȡ����
��3��	��ÿ�ַ���������ȡ���������Ļ�ϡ�
*/ 

#include <iostream>

enum balls { RED, YELLOW, BLUE, WHITE, BLACK };
char *color[] = { "red", "yellow", "blue", "white", "black" };
using namespace std;
int main()
{
	int i, j, k, cnt=0;
	for ( i=RED; i<=BLACK; i++ )
	    for( j=i; j<=BLACK; j++ )
	        for( k=j; k<=BLACK; k++ )
	            if ( i!=j && i!=k && j!=k )
	            {
	                cout << color[i] << " "
                         << color[j] << " "
                         << color[k] << endl;
					cnt ++;
				}
	cout << "Total " << cnt << " kinds selections." << endl;
	system( "pause" );
	return 0;
}
