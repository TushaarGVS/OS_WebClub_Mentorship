#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ipc.h>
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
  int msqid1, msqid2 ;
  key_t key1 = 1997, key2 = 2004 ;

  if((msqid1 = msgget(key1, 0666)) < 0) {
    cout << "msqid1 not created" << endl ;
    exit(1) ;
  }

  if((msqid2 = msgget(key2, 0666)) < 0) {
    cout << "msqid2 not created" << endl ;
    exit(1) ;
  }

  do {
    if(msgrcv(msqid1, &msgq, MAX_SIZE, 1, 0) < 0) {
      cout << "msgrcv() failed" << endl ;
      exit(1) ;
    }
    cout << "(Client-1) Received message: " << msgq.mtext << endl ;

    cout << "(Client-2) Enter a message: " ;
    cin >> msgq.mtext ;
    if(msgsnd(msqid2, &msgq, strlen(msgq.mtext)+1, IPC_NOWAIT) < 0) {
      cout << "msgsnd() failed" << endl ;
      exit(1) ;
    }
    /* Message sent */
  } while(strcmp(msgq.mtext, "Quit") != 0) ;
  return 0 ;
}
