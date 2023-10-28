#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int arr[4];

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
   
   printf("Sorted elements in child :- \n");
   for(int i=0; i<n; i++)
   {
     printf("%d",arr[i]);
     printf(" ");
   }
   printf("\n");
}

int main(int argc, char *argv[]) {
    //if (argc != 3) {
        //fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        //return 1;
    //}

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    
    for(int i=0; i<4; i++)
    {
      arr[i]=atoi(argv[i+3]);
    }
    
    bubbleSort(arr,4);
     
    int sum = num1 + num2;

    char result[100];
    sprintf(result, "Sum: %d\n", sum);

    // Write the result to stdout, which is redirected to the parent process
    printf("%s", result);

    return 0;
}

