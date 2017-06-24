#include <stdio.h>

int main(int argc, char *argv[]) {
  char buffer[128];
  while(1) {
    printf("$> ");
    scanf("%s", buffer);
  }

  return 0;
}
