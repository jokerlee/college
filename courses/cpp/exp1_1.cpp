/*
1��	�¼۸���Ϸ
��дC++����������¹��ܣ�
��1��	�ٶ���һ����Ʒ�������������ָ������Ʒ�ļ۸�1-1000����������
��2��	��ʾ�û��¼۸񣬲����룺���û��µļ۸����Ʒ�۸�߻�ͣ����û�������Ӧ����ʾ��
��3��	ֱ���¶�Ϊֹ����������ʾ��
*/

#include <iostream>
using namespace std;

int main()
{
	srand(time(NULL)); // initail random seed
	int num = rand()%1000+1, n;
	cout << "Here is a commodity, please guess its price:" << endl;
	while ( cin >> n && n != num )
	    if ( n > num )
	        cout << "high" << endl;
		else
		    cout << "low" << endl;
	cout << "You guess it. Congratulations!" << endl;
	
	system( "pause" );
	return 0;
}
