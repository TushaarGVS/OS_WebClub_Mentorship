#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main() {
  int n, a = 0, b = 1, c ;
  printf("Enter the number of terms: ") ;
  scanf("%d", &n) ;
  n = n - 2 ;
  pid_t pid = fork() ;
  if(pid == 0) {
    printf("Child process is executing\n") ;
    printf("Fibonacci Series: %d %d ", a, b) ;
    while(n-- > 0) {
      c = a + b ;
      a = b ;
      b = c ;
      printf("%d ", c) ;
    }
    printf("\nChild process is about to terminate\n") ;
  } else if(pid > 0) {
    printf("Parent process waits for child process\n") ;
    waitpid(pid, NULL, 0) ;
    printf("Parent process is about to terminate\n") ;
  } else
    printf("Child process is not created\n") ;
  return 0 ;
}
