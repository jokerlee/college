/*
4��	�ַ�����ת
��дC++����������¹��ܣ�
��1��	����һ���ַ�����
��2��	���ַ�����ת�Ժ��������Ҫ���ÿ⺯������
*/ 

#include <iostream>

using namespace std;

int main()
{
    char str[1000], *p, *q, tmp;
    cin.getline( str, 1000 );//����Դ�ַ��� 
    for ( q=str+0; *q!='\0'; q++ ) {}//�ҵ��ַ���β 
    for ( p=str+0, q--; q-p>=1; p++, q-- )
    {
        tmp = *p;
        *p = *q;
        *q = tmp;
    }
    cout << str << endl;
    system( "pause" );
    return 0;
}
