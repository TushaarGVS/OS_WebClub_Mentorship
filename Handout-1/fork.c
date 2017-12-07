#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
  for(int i = 0; i < 3; i++)
    fork() ;
  printf("Hello\n") ;
  return 0 ;
}
