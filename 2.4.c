#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

  char name[20];

  for(int i = 1; i < 5; i++) {
    pid_t pid = fork();

    if(pid == 0) {

     printf("Enter your name: ");
     scanf("%s", name);
     printf("Hello %s\n", name);
     exit(0);
    }
    else  {

      printf("Hello parent is here\n");
      printf("Waiting for child processes to finish...\n");
      wait(NULL);
      printf("child process finished.\n");
    }
  }
  printf("Job is done\n");
  return EXIT_SUCCESS;
}
