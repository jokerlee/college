/*
1��	��ʽIO��һ��
��дC++����������¹��ܣ�
��1��	ʹ��ofstream ��һ���ı��ļ�������������͵����ݣ������ļ��۲�����
 	�������޷������͡������͡������͡��ַ���������
��2��	��ʮ���ơ��˽��ơ�ʮ�����Ʒ�ʽ���ı��ļ������������
��3��	ʹ�ÿ��Ʒ��ͳ�Ա��������������ĸ�ʽ��
 	set���� precision() ...
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    int a;
	unsigned int b;
	long c;
	float d;
	char e[100];
	
    cout << "������һ������:";
    cin  >> a;
    cout << "������һ��������:";
    cin  >> b;    
    cout << "������һ��������:";
    cin  >> c;
    cout << "������һ��������:";
    cin  >> d;
    cout << "������һ���ַ���:";
    cin  >> e;	
		    
    ofstream fout( "61.txt" );
    fout << a << endl
         << c << endl
         << c << endl
         << setprecision(3) << d << endl
         << e << endl;
    fout << dec << a << endl
         << oct << a << endl
         << hex << a << endl;
    fout.close();
    cout << "�����ϣ����������61.txt��" << endl;
    
    system( "pause" );
    return 0;
}
