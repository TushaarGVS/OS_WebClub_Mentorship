#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std ;

int main(int argc, char *argv[]) {
  key_t key = 1997 ;
  int shmid ;
  
  if(argc == 2)
    key = atoi(argv[1]) ;

  if((shmid = shmget(key, 1000, SHM_R | SHM_W)) < 0) {
    cout << "shmget() failed" << endl ;
    exit(1) ;
  }
  
  char *shm = (char *) shmat(shmid, NULL, 0) ;
  if(shm == (char *) -1) {
    cout << "shmat() failed" << endl ;
    exit(1) ;
  }

  cout << "Received message: " << shm << endl ;
  return 0 ;
}
