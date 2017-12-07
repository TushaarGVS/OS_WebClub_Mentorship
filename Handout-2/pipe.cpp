#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std ;

int main(int argc, char *argv[]) {
  int pipe_fd[2], n ;

  if(pipe(pipe_fd) == -1) {
    cout << "Pipe failed" << endl ;
    exit(1) ;
  }
  
  cout << "Enter the number of fibonacci terms: " ;
  cin >> n ;

  int fibo[n+1] ;
  bool flag[n+1] = {false} ;
  fibo[0] = 0, fibo[1] = 1 ;
  
  pid_t pid = fork() ;
  if(pid == 0) {
    /* Child process: calculate fibonacci */
    cout << "CHILD:- calculating fibonacci" << endl ;
    for(int i = 2; i < n; i++)
      fibo[i] = fibo[i-1] + fibo[i-2] ;

    cout << "Fibonacci: " ;
    for(int i = 0; i < n; i++)
      cout << fibo[i] << " " ;
    cout << endl ;

    write(pipe_fd[1], fibo, sizeof(fibo)) ;
    close(pipe_fd[1]) ;
  } else if(pid > 0) {
    /* Patent process: calculate primes among fibonacci */
    cout << "PARENT:- waits for child to write" << endl ;
    wait(NULL) ;
    cout << "PARENT:- calculating primes among fibonacci" << endl ;

    read(pipe_fd[0], fibo, sizeof(fibo)) ;
    close(pipe_fd[0]) ;

    for(int i = 3; i < n; i++)
      for(int j = 2; j*j <= fibo[i]; j++)
	if(fibo[i] % j == 0) {
	  flag[i] = true ;
	  break ;
	}

    cout << "Primes among fibonacci: " ;
    for(int i = 3; i < n; i++)
      if(!flag[i])
	cout << fibo[i] << " " ;
    cout << endl ;
  } else
    cout << "Fork failed" << endl ;
  return 0 ;
}
