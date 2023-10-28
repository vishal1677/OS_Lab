#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
int arr[5];
 printf("Enter elements:- ");
 for(int i=0; i<5; i++)
 {
   scanf("%d", &arr[i]);
 }
 
 int cpid = fork();
 int ch_id=getpid();
 int pr_id=getppid();
 
 
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {    /* Child reads from pipe */
            bubbleSort(arr,5);
            sleep(1);
            printf("\n");
            printf("Process id is :- %d ",getpid());
            printf("\n");
            printf("Parent process id is :- %d",getppid());
            printf("\n");
       
            
           } else {            /* Parent writes argv[1] to pipe */
             printf("This is Parent");
             sleep(30);
             wait(NULL);
           }
}
