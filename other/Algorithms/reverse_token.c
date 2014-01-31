#include <stdio.h>
#include <string.h>
#define MAX 100

void reverse_token() {
  char str[MAX] = {0};
  if (scanf("%[^#|\0]", str) != EOF)
  {
      getchar();
      reverse_token();
      printf("%s ", str);
  }
}

int main()
{
    reverse_token();
}
