#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int compare_function(const void *a, const void *b) {
  return *(int *)a - *(int *)b ;
}

void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 =  r - m;
  
  int L[n1], R[n2];
  
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1+ j];
  
  i = 0, j = 0, k = l; 
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  
  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}
 
void merge_sort(int arr[], int l, int r) {
  if (l < r) {
    int m = l+(r-l)/2;
    merge_sort(arr, l, m);
    merge_sort(arr, m+1, r);  
    merge(arr, l, m, r);
  }
}

int main() {
  int n ;
  printf("Enter the number of elements: ") ;
  scanf("%d", &n) ;
  int a[n+1] ;
  printf("Enter the array elements: ") ;
  for(int i = 0; i < n; i++)
    scanf("%d", &a[i]) ;
  pid_t pid = fork() ;
  if(pid == 0) {
    printf("Child process is computing - Quick Sort\nSorted array: ") ;
    qsort(a, n, sizeof(int), compare_function) ;
    for(int i = 0; i < n; i++)
      printf("%d ", a[i]) ;
    printf("\nChild process is about to terminate\n") ;
  } else if(pid > 0) {
    printf("Parent process waits for child process\n") ;
    waitpid(pid, NULL, 0) ;
    printf("Parent process is computing - Merge Sort\nSorted array: ") ;
    merge_sort(a, 0, n-1) ;
    for(int i = 0; i < n; i++)
      printf("%d ", a[i]) ;
    printf("\nParent process is about to terminate\n") ;
  } else
    printf("Child process is not created\n") ;
  return 0 ;
}
