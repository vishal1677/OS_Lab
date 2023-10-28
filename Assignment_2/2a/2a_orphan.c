#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int arr[5];
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
   
   for(int i=0; i<n; i++)
   {
     printf("%d",arr[i]);
     printf(" ");
   }
}

int main()
{
 printf("Enter elements:- ");
 for(int i=0; i<5; i++)
 {
   scanf("%d", &arr[i]);
 }
 
 int cpid = fork(); // fork will create new process

 
 
 
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE); // error occured and process id is negative
           }

           if (cpid == 0) {    /* Child process */
            bubbleSort(arr,5);
            printf("\n");
            printf("Child Process id is :- %d ",getpid());
            printf("\n");
            printf("Parent process id is :- %d",getppid());
            printf("\n");
            sleep(5);
            printf("\n");
            printf("Child Process id is :- %d ",getpid());
            printf("\n");
            printf("Parent process id is :- %d",getppid());
            printf("\n");

            
           } else {   
             sleep(1);         /* Parent writes argv[1] to pipe */
             printf("I am parent my pid is %d",getpid);
             //wait(NULL);
           }
}
