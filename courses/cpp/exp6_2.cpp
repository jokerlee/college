/*
2��	��ʽIO������
��дC++����������¹��ܣ�
��1��	����һ���ı��ļ���
��2��	ʹ��ofstream ��һ���������ļ�������������͵����ݣ������ļ��۲�����
 	�������޷������͡������͡������͡��ַ���������
*/

#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

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
		    
    ofstream fout( "62.txt", ios_base::binary );
    fout << a << endl
         << c << endl
         << c << endl
         << setprecision(3) << d << endl
         << e << endl;
    fout << dec << a << endl
         << oct << a << endl
         << hex << a << endl;
    fout.close();
    cout << "�����ϣ����������62.txt��" << endl;
    
    system( "pause" );
    return 0;
}
