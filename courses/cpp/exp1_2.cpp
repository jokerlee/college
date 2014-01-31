/*
2、	计算 N 以内的所有素数
编写C++程序完成以下功能：
（1）	提示用户输入N；
（2）	计算出从2到N之间的所有素数；
（3）	将结果保存在write.txt中。
*/

#include<iostream>
#include<fstream>
using namespace std;

int isprim(int n) //素数测试函数 
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
		cerr << "文件打开失败" << endl; 
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
