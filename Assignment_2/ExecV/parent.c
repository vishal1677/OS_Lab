#include<sys/wait.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void bubbleSort(int arr[], int n)
{
   for(int i=0; i<n; i++)
   {
     for(int j=0; j<n-i-1;j++)
     {
       if(arr[j+1]<arr[j])
       {
         int temp=arr[j+1];
         arr[j+1]=arr[j];
         arr[j]=temp;
         
       }
     }
   }
   
   printf("Sorted elements in parent:- \n");
   for(int i=0; i<n; i++)
   {
     printf("%d",arr[i]);
     printf(" ");
   }
   printf("\n");
}


int main()
{
   int arr[4];
   
   printf("Enter 4 elements:- \n"); 
   for(int i=0; i<4; i++)
   {
     scanf("%d", &arr[i]);
   }
   
 pid_t cpid;
 cpid=fork();
 
 
 if(cpid == -1)
 {
   perror("fork");
   exit(EXIT_FAILURE);
 }
 
 if(cpid == 0)
 {
  sleep(1);
  printf("In child process %d\n",getpid());
  char str[4][20];
  for(int i=0; i<4; i++)
  {
    sprintf(str[i],"%d",arr[i]);
  }
  char *path="./child.out";
  char *args[]={path,str[0],str[1],str[2],str[3],NULL};
  execv(path,args);
 }
 else if(cpid >0)
 {
   printf("In parent process %d\n",getpid());
   bubbleSort(arr,4);
   wait(NULL);
 }

return 0;
}
