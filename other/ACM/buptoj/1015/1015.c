/* BUPT OJ 1015
 * 2010-05-31
 * 简单的模拟，注意数据范围，int会溢出
 * jokerleee@gmail.com
 */


// n1/d1 opt n2/d2
#include <stdio.h>

long long gcd(long long a, long long b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main()
{
    long long T, d1, d2, n1, n2, n, d, t, s;
    char opt[10];

    scanf("%lld", &T);
    while (T--)
    {
        scanf("%s %lld %lld %lld %lld", &opt, &d1, &n1, &d2, &n2);
        switch (opt[0])
        {
        case '+':
            d = d1 * d2;
            n = n1 * d2 + n2 * d1;
            break;
        case '-':
            d = d1 * d2;
            n = n1 * d2 - n2 * d1;
            break;
        case '/':
            t = d2; d2 = n2; n2 = t;
        case '*':
            d = d1 * d2;
            n = n1 * n2;
            break;
        }
        
        if (n > 0 && d < 0 || n < 0 && d > 0) putchar('-');
        n = n > 0 ? n : -n;
        d = d > 0 ? d : -d;
        t = gcd(n > d ? n : d, n > d ? d : n);
        printf("%lld/%lld\n", n/t, d/t);
    }
    return 0;
}


