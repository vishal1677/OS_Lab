#include<stdio.h>
int n=5;
int m=3;

int issafe(int alloc[n][m],int need[n][m],int aval[m] , int safeseq[n])
{

 int allocCopy[n][m];
 int needCopy[n][m];
 int work[m];
 int ind=0;

 for(int i=0; i<n; i++)
 {
    for(int j=0; j<m; j++)
    {

    allocCopy[i][j]=alloc[i][j];
    needCopy[i][j]=need[i][j]; 

    }
 }

 for(int i=0; i<m; i++)
 {
  work[i]=aval[i];
 }

 int isvis[n];
 for(int i=0; i<n; i++)
 {
    isvis[i]=0;
 }




  while (1)
  {
    // in each iteration check if your work matrix is updated 
    int isfound=0;

    for(int i=0; i<n; i++)
    {
      int istrue=0;
      if(!isvis[i]){

      for(int j=0; j<m; j++)
      {
        if(need[i][j] > work[j])
        {
            istrue=1;
            break;
        }
      }
      // istrue =0 => pi can be execute
      if(!istrue)
      {
        isvis[i]=1;
        for(int j=0; j<m; j++)
        {
          work[j]+=alloc[i][j];  
        }

        if(ind < n){
        safeseq[ind]=i;
        ind++;
        }

        isfound=1;
      }   
      }
    }

    if(!isfound)
    {
     break;
    }
  }
  
  for(int i=0; i<n; i++)
  {
    if(!isvis[i])
    {
        return 0;
    }
  }

return 1;
}


void bankersAlgo()
{
int m=5; // no of processes 
int n=3;

}



int main()
{
int n = 5; // Number of processes
int m = 3; // Number of resources
int alloc[5][3] = { { 0, 1, 0 }, // P0 // Allocation Matrix
{ 2, 0, 0 }, // P1
{ 3, 0, 2 }, // P2
{ 2, 1, 1 }, // P3
{ 0, 0, 2 } }; // P4

int max[5][3] = { { 7, 5, 3 }, // P0 // MAX Matrix
{ 3, 2, 2 }, // P1
{ 9, 0, 2 }, // P2
{ 2, 2, 2 }, // P3
{ 4, 3, 3 }}; // P4

int ava[3]={3,3,2};
int need[5][3];

for(int i=0; i<5; i++)
{
 for(int j=0; j<3; j++)
 {
    need[i][j]=max[i][j]-alloc[i][j];
 }
}


while (1)
{

 printf("Enter your choice\n");
 printf("1) Display current state\n");
 printf("2) Calculate Need\n");
 printf("3) Check saftey\n");
 printf("4) Accept request\n");
 printf("5) Exit\n");
 int ch; 
 scanf("%d",&ch);

 if(ch ==  1)
 {
   printf("Allocation\n");
   for(int i=0; i<5; i++)
   {
    for(int j=0; j<3; j++)
    {
     printf("%d\t",alloc[i][j]);
    }
    printf("\n");
   }

   printf("Max\n");
   for(int i=0; i<5; i++)
   {
    for(int j=0; j<3; j++)
    {
     printf("%d\t",max[i][j]);
    }
    printf("\n");
   }

   printf("Available\n");
   for(int i=0; i<3; i++)
   {
    printf("%d\t",ava[i]);
   }
 }
 else if(ch == 2)
 {
  printf("Need\n");
  for(int i=0; i<5; i++)
  {
    for(int j=0; j<3; j++)
    {
     printf("%d\t",need[i][j]);
    }
    printf("\n");
  }
 }
 else if(ch == 3)
 {
  int safeseq[n];

   int flag=issafe(alloc,need,ava,safeseq);
   if(flag)
   {
    printf("System is in safe state and saftey sequence is\n");
    for(int i=0; i<n; i++)
    {
     printf("p%d\n",safeseq[i]);
    }
   }
   else
   {
    printf("System is not in safe sequence\n");
   }
 }
 else if(ch == 4)
 {
  int req1[]={1,0,2};
  // if req1 <= need1
  int f1=1;
  int f2=1;

  for(int i=0; i<m; i++)
  { 
    if(need[1][i] < req1[i])
    {
     f1=0;
    }

    if(ava[i] < req1[i])
    {
        f2=0;
    }
  }

  if(f1 && f2)
  {
    printf("Request is valid checking the safety\n");
    for(int i=0; i<m; i++)
    {
     need[1][i]-=req1[i];
     alloc[1][i]+=req1[i];
     ava[i]-=req1[i];
    }

    int safeseq[n];
    int flag=issafe(alloc,need,ava,safeseq);
    
    if(flag)
    {
        printf("System is safe and saftey sequenece is \n");
        for(int i=0; i<n; i++)
        {
          printf("p%d\n",safeseq[i]);
        }
    }

  }


 }
 else if(ch == 5)
 {
   break;
 }


}


return 0;
}
