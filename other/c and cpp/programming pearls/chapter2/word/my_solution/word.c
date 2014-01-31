#include <stdio.h>
#include <string.h>

#define N 80000
#define MAX_LEN 50

struct srt{
    int idx;
    char word[MAX_LEN];
}sign[N];

char dict[N][MAX_LEN] = {0};

int charcmp(const void * a, const void * b)
{
    return *(char *)a - *(char *)b;
}

int stringcmp(const void * a, const void * b)
{
    return strcmp(((struct srt *)a)->word, ((struct srt *)b)->word);
}

int main()
{
    FILE * ifp;
    int n, i, flg;
    ifp = fopen("dict.dat", "r");
    
    n = 0;
    while (fscanf(ifp, "%s", &dict[n]) != EOF)
    {
        sign[n].idx = n;
        strncpy(sign[n].word, dict[n], MAX_LEN);
        n++;
    }

    for (i = 0; i < n; ++i)
        qsort(sign[i].word, strlen(sign[i].word), sizeof(char), charcmp);

    qsort(sign, n, sizeof(struct srt), stringcmp);

    for (i = 0, flg = 0; i < n-1; ++i)
    {
        if (strcmp(sign[i].word, sign[i+1].word) == 0)
        {
            printf("%s ", dict[sign[i].idx]);
            flg = 1;
        }
        else
        {
            if (flg == 1)
                printf("%s\n", dict[sign[i].idx]);
            flg = 0;
        }
    }

    return 0;
}
