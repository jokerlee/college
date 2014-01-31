/* BUPT OJ 1081 Bovine Latin
 * 2010-06-02 20:02
 * 水题，简单的字符串操作
 * jokerleee@gmail.com
 * */

#include <stdio.h>
int main()
{
    int N; char bf[41]; scanf("%d", &N);
    while (N--)
    {
        scanf("%s", bf);
        if (bf[0]=='a' || bf[0]=='e' || bf[0]=='i' || bf[0]=='o' || bf[0]=='u')
            printf("%scow\n", bf);
        else printf("%s%cow\n", bf+1, bf[0]);
    }
    return 0;
}
