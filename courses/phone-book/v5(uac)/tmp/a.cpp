#include <stdio.h>

int main()
{
    long a = 0;
    FILE * fp = fopen("info", "w");
    fwrite((char*)&a, sizeof(a), 1, fp);
}
