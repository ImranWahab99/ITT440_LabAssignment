#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

int main(void)
{

  void sigint_handler(int sig);
  int n, i, flag = 0;

  if (signal(SIGINT, sigint_handler) == SIG_ERR){
     perror("signal");
     exit(1);
  }

  printf("Please enter a number: ");
  scanf("%d", &n);

  if (n == 0 || n == 1)
     flag = 1;

  for (i = 2; i <= n / 2; ++i) {
      if (n % i == 0) {
       flag = 1;
       break;
     }
   }

   if (flag == 0)
     printf("%d is a prime number. \n", n);
   else
     printf("%d is not a prime number. \n", n);

 return 0;
}

void sigint_handler(int sig)
{
  printf("\nJob is done \n");
  exit(1);
}
