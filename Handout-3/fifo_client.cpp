#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

using namespace std ; 

int main(int argc, char *argv[]) {
  int request = open("request.fifo", O_WRONLY) ;
  int result = open("result.fifo", O_RDONLY) ;
  char file_name[100], file_content[2048] ;
  int bytes ;

  if(request == -1 && result == -1) {
    cout << "Fifo failed" << endl ;
    exit(1) ;
  }

  cout << "Enter the file name: " ;
  cin >> file_name ;
  write(request, file_name, sizeof(file_name)) ;

  while((bytes = read(result, file_content, sizeof(file_content))) > 0)
    write(1, file_content, bytes) ;

  close(request) ;
  close(result) ;
  return 0 ;
}
