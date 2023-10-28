#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

void bubblesort(int arr[], int n)
{
  for(int i=0; i<n-1; i++)
  {
   for(int j=0; j<n-i-1; j++)
   {
     if(arr[j+1] < arr[j])
     {
      int temp=arr[j+1];
      arr[j+1]=arr[j];
      arr[j]=temp;
     }
   }
  }
  printf("\n");
  printf("The sorted arry is :-\n");
  for(int i=0; i<n; i++)
  {
   printf("%d ",arr[i]);
  }
  
  printf("\n");
}

int main()
{
 printf("Enter size of arry :- \n");
 int n; 
 scanf("%d",&n);
 int *arr=(int*)malloc(n*sizeof(int));
 printf("Enter %d elements of array\n",n);
 for(int i=0; i<n; i++)
 {
  scanf("%d",&arr[i]);
 }
 
 pid_t cpid=fork();
 
 if(cpid == -1)
 {
  perror("fork");
  exit(EXIT_FAILURE);
 }
  
 if(cpid == 0)
 {
   bubblesort(arr,n);
   printf("\n");
   printf("Parent process id %d \n",getppid());
   printf("Child process id %d \n",getpid());
   sleep(5);
   printf("\n");
   printf("Parent process id %d \n",getppid());
   printf("Child process id %d \n",getpid());
 }
 else
 {
    sleep(1);
    printf("This is a parent process with pid %d\n",getpid());    
 }
 
return 0;
}

