#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>


void bubbleSort(int arr[], int n)
{
   for(int i=0; i<n; i++)
   {
     for(int j=0; j<n-i-1;j++)
     {
       if(arr[j+1] > arr[j])
       {
         int temp=arr[j+1];
         arr[j+1]=arr[j];
         arr[j]=temp;
         
       }
     }
   }
   
   printf("Sorted elements in child:- \n");
   for(int i=0; i<n; i++)
   {
     printf("%d",arr[i]);
     printf(" ");
   }
   printf("\n");
}

int main(int argc, char *argv[])
{
 int arr[4];
 printf("Child process id %d\n",getpid());
 for(int i=0; i<4; i++)
 {
  arr[i]=atoi(argv[i+1]); 
 }
 bubbleSort(arr,4);

return 0;
}


