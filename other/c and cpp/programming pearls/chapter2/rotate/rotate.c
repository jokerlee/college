#include <stdio.h>
#include <string.h>

char str[] = "abcdefgh";

void reverse(int from, int to)
{
    char * right = str + to;
    char * left = str + from;
    char ch;
    while (left < right)
    {
        ch = *left;
        *left++ = *right;
        *right-- = ch;
    }
}

void rotate(int i, int n)
{
    reverse(0, i-1);
    reverse(i, n-1);
    reverse(0, n-1);
}

int main()
{
    rotate(3, 8);
    printf("%s\n", str);
    return 0;
}
