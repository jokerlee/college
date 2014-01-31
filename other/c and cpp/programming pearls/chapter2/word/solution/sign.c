#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50 

int charcomp(const void * x, const void * y)
{
    return *(char *)x - *(char *)y;
}

int main()
{
    char word[MAX_LEN], sig[MAX_LEN];
    while (scanf("%s", word) != EOF)
    {
        strcpy(sig, word);
        qsort(sig, strlen(sig), sizeof(char), charcomp);
        printf("%s %s\n", sig, word);
    }
    fclose(ifp);
    return 0;
}
