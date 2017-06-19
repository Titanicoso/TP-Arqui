#include <stdio.h>

int main() {
  char buffer[128];
  while(1) {
    printf("$> ");
    scanf("%s", buffer);
  }

  return 0;
}
