/*
Name Vishal Sharad PAtil
Roll No 33158
*/


#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int arr[4];
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

int main() {
    int pipefd[2];
    pid_t cpid;
    char buf;

    int a, b;
    printf("Enter 1 number: ");
    scanf("%d", &a);
    printf("Enter 2 number: ");
    scanf("%d", &b);
    printf("Enter 4 elements:- \n");
    
    for(int i=0; i<4; i++)
    {
      scanf("%d", &arr[i]);
    }

    if (pipe(pipefd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();

    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        //close(pipefd[0]); 
        sleep(1);
        char str1[20];
        char str2[20];
        
        char str3[20];
        char str4[20];
        char str5[20];
        char str6[20];
        
    
        sprintf(str1, "%d", a);
        sprintf(str2, "%d", b);
        
        sprintf(str3, "%d", arr[0]);
        sprintf(str4, "%d", arr[1]);
        sprintf(str5, "%d", arr[2]);
        sprintf(str6, "%d", arr[3]);

        

        char *path = "./child.out";
        char *args[] = {path, str1, str2,str3,str4,str5,str6,NULL};
        execv(path, args);
    } else if (cpid > 0) {
        bubbleSort(arr,4);
        wait(NULL); 

    }

    return 0;
}

