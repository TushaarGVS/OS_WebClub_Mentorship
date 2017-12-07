#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <fcntl.h>

using namespace std ;

int main(int argc, char *argv[]) {
  key_t key = 1997 ;
  int shmid, n, first = 0, second = 1 ;

  if(argc == 2)
    key = atoi(argv[1]) ;
  
  if((shmid = shmget(key, 1000, SHM_R | SHM_W)) < 0) {
    shmid = shmget(key, 1000, SHM_R | SHM_W | IPC_CREAT) ;
    if(shmid < 0) {
      cout << "shmget() failed" << endl ;
      exit(1) ;
    }
  }

  pid_t pid = fork() ;
  if(pid == 0) {
    int *shm = (int *) shmat(shmid, NULL, 0) ;
    if(shm == (int *) -1) {
      cout << "shmat() failed" << endl ;
      exit(1) ;
    }

    cout << "Enter the number of terms: " ;
    cin >> n ;

    *shm++ = first ;
    *shm++ = second ;
    for(int i = 2; i < n; i++) {
      int next = first + second ;
      *shm++ = next ;
      first = second ;
      second = next ;
    }
    *shm = -1 ;
  } else if(pid > 0) {
    wait(NULL) ;

    if((shmid = shmget(key, 1000, SHM_R | SHM_W)) < 0) {
      cout << "shmget() failed" << endl ;
      exit(1) ;
    }

    int *shm = (int *) shmat(shmid, NULL, 0) ;
    if(shm == (int *)-1) {
      cout << "shmat() failed" << endl ;
      exit(1) ;
    }

    cout << "Fibonacci: " ;
    for(int *i = shm; *i != -1; *i++)
      cout << *i << " " ;
    cout << endl ;

    if(shmdt(shm) == -1) {
      cout << "shmdt() failed" << endl ;
      exit(1) ;
    }
  } else
    cout << "Fork failed" << endl ;
  return 0 ;
}
