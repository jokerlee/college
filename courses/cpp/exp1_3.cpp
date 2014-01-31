/*
3、	袋中取球
编写C++程序完成以下功能（使用 enum）：
（1）	袋子中有 red, yellow, blue, white, black 五种颜色的球多个；
（2）	一次从袋子里取出3个颜色不同的球，有几种取法；
（3）	将每种方法的所有取法输出到屏幕上。
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
