/* BUPT OJ 1059
 * 2010-06-01 16:41
 * һ������������⣬��Ϊ�ǹ̶���C(9,7)��ת��C(9,2)ֱ��ѭ�����
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int main()
{
    int i, j, k, a[9];
    for (i=0; i<9; ++i) scanf("%d", &a[i]);
    for (i=0,k=0; i<9; ++i) k += a[i];
    for (i=0; i<9; ++i) 
    {
        for (j=0; j<9; ++j)
            if (i!=j && k-a[i]-a[j]==100)
                break;
        if (j!=9) break;
    }
    for (k=0; k<9; ++k) if (k!=i && k!=j) printf("%d\n", a[k]);
    return 0;
}
