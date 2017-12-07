#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main() {
  pid_t pid = fork() ;
  if(pid == 0) {
    printf("Child process in under execution\n") ;
    printf("Child process is about to terminate\n") ;
    exit(0) ;
  } else if(pid > 0) {
    printf("Parent process in under execution\n") ;
    sleep(15) ;
    printf("Parent process in about to terminate\n") ;
  } else
    printf("Child process has not been created\n") ;
  return 0 ;
}
