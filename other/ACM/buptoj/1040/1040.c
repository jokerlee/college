/* BUPT OJ 1040 神奇的SuperCow
 * 2010-06-02 19:50
 * 比较有技巧的题目，不能直接乘，会溢出；因为数字范围0~16，统计所有乘数和
 *    除数的个数，相同的乘数和除数可以约掉
 * jokerleee@gmail.com
 * */

#include <stdio.h>
#include <ctype.h>
int main()
{
    char exp[3]; int n, i, s, d, c[16]={0};
    scanf("%d", &n);
    for (i=0,s=1; i<n; ++i)
    {
        scanf("%s", exp);
        d = isdigit(exp[1]) ? exp[1]-'0' : exp[1]-'A' + 10;
        int sn = exp[0] == '*' ? 1 : -1;
        switch(d)
        {
            case 2: case 3: case 5: case 7: case 11: case 13:
                c[d]+=sn; break;
            case  0: c[0]++; break;
            case  4: c[2]+=2*sn; break;
            case  6: c[2]+=sn; c[3]+=sn; break;
            case  8: c[2]+=3*sn; break;
            case  9: c[3]+=2*sn; break;
            case 10: c[2]+=sn; c[5]+=sn; break;
            case 12: c[2]+=2*sn; c[3]+=sn; break;
            case 14: c[2]+=sn; c[7]+=sn; break;
            case 15: c[3]+=sn; c[5]+=sn; break;
        }
    }
    if (c[0] != 0) printf("0\n");
    else { 
        for (i=2; i<16; ++i) 
            if (c[i] > 0) while (c[i]--) s *= i;
            else if (c[i] < 0) while (c[i]++) s /= i;
        printf("%d\n", s); }
    return 0;
}
