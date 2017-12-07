#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std ;

int main(int argc, char *argv[]) {
  int pipe_1_fd[2], pipe_2_fd[2] ;
  char name[100], age[100] ;

  if(pipe(pipe_1_fd) == -1) {
    cout << "Pipe-1 failed" << endl ;
    exit(1) ;
  }

  if(pipe(pipe_2_fd) == -1) {
    cout << "Pipe-2 failed" << endl ;
    exit(1) ;
  }
  
  pid_t pid = fork() ;
  if(pid == 0) {
    cout << "CHILD:- Enter your name: " ;
    cin >> name ;
    cout << "CHILD:- Nice to meet you, " << name << endl ;

    write(pipe_1_fd[1], name, sizeof(name)) ;
    close(pipe_1_fd[1]) ;

    sleep(2) ;
    
    read(pipe_2_fd[0], age, sizeof(age)) ;
    close(pipe_2_fd[0]) ;

    cout << "CHILD:- Hello sir, your age is: " << age << endl ;
  } else if(pid > 0) {
    sleep(2) ;
    
    read(pipe_1_fd[0], name, sizeof(name)) ;
    close(pipe_1_fd[0]) ;

    cout << "PARENT:- It's my pleasure to meet you, " << name << endl ;
    cout << "PARENT:- Enter your age: " ;
    cin >> age ;

    write(pipe_2_fd[1], age, sizeof(age)) ;
    close(pipe_2_fd[1]) ;
  } else
    cout << "Fork failed" << endl ;
}
