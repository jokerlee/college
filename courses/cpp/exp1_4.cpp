/*
4��	�˷��ھ���
��дC++����������¹��ܣ�
��1��	����˷��ھ���
��2��	�Ҷ�����ʾ�� 
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int i=1, j=1, n=0;
    
    for ( i=1; i<=9; i++ )
    {
		for ( j=1; j<i; j++ )//��ǰ���� 
		    cout << "        "; 
		for ( j=i; j<=9; j++ )
		    cout << i << '*' << j << '=' << setw(4) << left << i*j;
		cout << endl;
	}
	
    system ("pause");
    return 0;
}
