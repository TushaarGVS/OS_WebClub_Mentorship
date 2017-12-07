#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std ;

int main(int argc, char *argv[]) {
  mkfifo("request.fifo", 0777) ;
  mkfifo("result.fifo", 0777) ;

  int request = open("request.fifo", O_RDONLY) ;
  int result = open("result.fifo", O_WRONLY) ;
  char file_name[100], file_content[2048] ;
  int bytes ;

  if(request == -1 && result == -1) {
    cout << "Fifo failed" << endl ;
    exit(1) ;
  }

  cout << "Waiting for the file name!" << endl ;
  read(request, file_name, sizeof(file_name)) ;
  cout << "File name: " << file_name << endl ;

  int file_fd = open(file_name, O_RDONLY) ;
  if(file_fd >= 0)
    while((bytes = read(file_fd, file_content, sizeof(file_content))) > 0)
      write(result, file_content, bytes) ;

  close(request) ;
  close(result) ;
  unlink("request.fifo") ;
  unlink("result.fifo") ;
  return 0 ;
}
