#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <fcntl.h>

#define MAX_SIZE 128
using namespace std ;

struct msg_buf {
  long mtype ;
  char mtext[MAX_SIZE] ;
} ;

int main(int argc, char *argv[]) {
  struct msg_buf msgq ;
  key_t key = 1997 ;
  int msqid ;
  
  if((msqid = msgget(key, 0666)) < 0) {
    cout << "msgget() failed" << endl ;
    exit(1) ;
  }
  
  if(msgrcv(msqid, &msgq, MAX_SIZE, 1, 0) < 0) {
    cout << "msgrcv() failed" << endl ;
    exit(1) ;
  }
  
  cout << "Received message: " << msgq.mtext << endl ;
  return 0 ;
}
