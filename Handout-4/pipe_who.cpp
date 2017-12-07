#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std ;

int main(int argc, char *argv[]) {
  int pipe_fd[2] ;
  if(pipe(pipe_fd) == -1) {
    cout << "Pipe failed" << endl ;
    exit(1) ;
  }

  pid_t pid = fork() ;
  if(pid == 0) {
    close(1) ;
    dup(pipe_fd[1]) ;
    close(pipe_fd[0]) ;
    execlp("who", "who", NULL) ;
  } else if(pid > 0) {
    close(0) ;
    dup(pipe_fd[0]) ;
    close(pipe_fd[1]) ;
    execlp("wc", "wc", "-l", NULL) ;
  } else
    cout << "Fork failed" << endl ;
  return 0 ;
}
