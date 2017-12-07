#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <fcntl.h>

#define MAX_SIZE 128
using namespace std ;

struct msg_buf {
  long mtype ;
  char mtext[MAX_SIZE] ;
} ;

int main(int argc, char *argv[]) {
  struct msg_buf msgq ;
  int msqid ;
  key_t key = 1997 ;

  if((msqid = msgget(key, IPC_CREAT | 0666)) < 0) {
    cout << "msgget() failed" << endl ;
    exit(1) ;
  }

  msgq.mtype = 1 ;
  cout << "Enter a message: " ;
  cin >> msgq.mtext ;
  
  if(msgsnd(msqid, &msgq, strlen(msgq.mtext)+1, IPC_NOWAIT) < 0) {
    cout << "msgsnd() failed" << endl ;
    exit(1) ;
  }
  cout << "Message sent!" << endl ;
  return 0 ;
}
