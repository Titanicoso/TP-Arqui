#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
#include <time.h>

extern int int80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx);

static const char * man =
"time: Prints out the current time\n\
date: Prints out the current date\n\
timezone *number*: Changes the timezone\n\
clear: Wipes out the screen\n\
echo *string*: Prints out the string\n\
execute *module*: Executes the module";

int main(int argc, char *argv[]) {
  char buffer[128];
  while(1) {
    printf("$> ");
    scanf("%s", buffer);
    execute(buffer);
  }

  return 0;
}

void execute(char * buffer) {
  char auxBuffer[128];
  int timezone;

  if(strcmp(buffer, "help") == 0 || strcmp(buffer, "man") == 0) {
    printf("%s\n", man);
  }
  else if(strcmp(buffer, "time") == 0) {
    printf("%d:%d:%d\n", getHour(), getMinutes(), getSeconds());
  }
  else if(strcmp(buffer, "date") == 0) {
    printf("%d/%d/%d\n", getDay(), getMonth(), getYear());
  }
  else if(sscanf("timezone %d", buffer,&timezone) == 1) {
    setTimeZone(timezone);
  }
  else if(strcmp(buffer, "clear") == 0) {
    int80(2,0,0,0);
  }
  else if(sscanf("echo %s", buffer, auxBuffer) == 1) {
    printf("%s\n", auxBuffer);
  }
  else if(sscanf("execute %s", buffer, auxBuffer) == 1) {
    if(execv(auxBuffer,0,0) == -1)
      printf("Invalid Module\n");
  }
  else
    printf("%s: Invalid command\n", buffer);
}

int execv(char *filename, int argc, char *argv[]) {
	return int80(7, filename, argc, argv);
}
