#include <stdio.h>
#include <string.h>
#define MAX_LEN 50

int main()
{
    char word[MAX_LEN], oldword[MAX_LEN], 
         sig[MAX_LEN], oldsig[MAX_LEN];
    int flg = 0;
    strcpy(oldsig, "");
    strcpy(oldword, "");
    while (scanf("%s %s", sig, word) != EOF)
    {
        if (strcmp(oldsig, sig) == 0)
        {
            if (flg == 0)
            {
                printf("%s ", oldword);
                flg = 1;
            }
            printf(" %s", word);
        }
        else
        {
            if (flg == 1)  putchar('\n');
            flg = 0;
        }
        strcpy(oldsig, sig);
        strcpy(oldword, word);
    }
    return 0;
}
