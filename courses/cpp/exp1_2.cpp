/*
2��	���� N ���ڵ���������
��дC++����������¹��ܣ�
��1��	��ʾ�û�����N��
��2��	�������2��N֮�������������
��3��	�����������write.txt�С�
*/

#include<iostream>
#include<fstream>
using namespace std;

int isprim(int n) //�������Ժ��� 
{
    for (int i=2; i*i<=n; i++)
        if (n%i==0)
			return 0;
	return 1;
}

int main()
{
	ofstream fout( "write.txt" );
	if (!fout)
		cerr << "�ļ���ʧ��" << endl; 
	else
	{
	    int N, i=1;
	    cout << "Please input a N: ";
	    cin >> N;
	    while (++i<=N)
	    	if (isprim(i)==1)
	        	fout << i << endl;
	    fout.close();
	
	    cout << "Finish." << endl;
	}
    system("pause");
    return 0;
}
