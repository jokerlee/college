/* 
3��	��ʽIO������
��дC++����������¹��ܣ�
��1��	����һ���ı��ļ�����
��2��	���ļ������ڸ��ļ���ÿһ��ǰ�����һ���кţ�����������һ���ı��ļ��С�
*/ 

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string line;
    char filename[100];
    cout << "������Դ�ļ�����";
    cin >> filename;
    ifstream fin( filename, ios_base::in );
    ofstream fout( "out.txt", ios_base::out );
    int i=1;
    if ( fin )
    {
	    while ( fin )
	    {
	        getline(fin, line);
	        fout << i++ << " " << line << endl;
	    }
	    cout << "�༭���,���������out.txt��" << endl;
	}
    else
        cerr << "�ļ���ʧ��" << endl;
    system( "pause" );
    return  0;
}
