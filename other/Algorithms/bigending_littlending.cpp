#include <cstdio>

unsigned long chars_to_ulong(char str[])
{
    unsigned long ret=0;
    for (int i=0; str[i] != 0; i++)
        ret = ret*10 + (str[i]-'0');
    return ret;
}

int main(int argc, char * argv[])
{
    if (argc==2)
    {
        unsigned long t = chars_to_ulong(argv[1]);
        t =  ((t & 0x000000ff) << 24) | ((t & 0x0000ff00) << 8)
           | ((t & 0x00ff0000) >> 8) | ((t & 0xff000000) >> 24);
        printf("%ul\n", t);
        return 0;
    }
    
}
