#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define  maxsize 199

void SSTF(int request[], int hp, int n)
{
 int vis[n];
 for(int i=0; i<n; i++)
 {
  vis[i]=0;
 }
 
 int ind=1;
 int ele=hp;
 int seektime=0;
 
 for(int i=0; i<=n; i++)
 {
  printf("%d\t%d\n",ind,ele);
  ind++;
  
  int minidiff=1e6;
  int miniele=ele;
  int ptr=0;
  
  for(int i=0; i<n; i++)
  {
    if(minidiff > abs(request[i]-ele) && !vis[i])
    {
       minidiff=abs(request[i]-ele);
       miniele=request[i];
       ptr=i;
    }
  }
  
  vis[ptr]=1;
  seektime+=(abs(ele-miniele));
  ele=miniele;
 }
 
 printf("Total seek time %d :-\n",seektime);
 
}

void sort(int arr[], int n)
{
 for(int i=0; i<n; i++)
 {
  for(int j=0; j<n-i-1; j++)
  {
    if(arr[j] > arr[j+1])
    {
       int temp=arr[j+1];
       arr[j+1]=arr[j];
       arr[j]=temp;
    }
  }
 }
 
}

void SCAN(int request[], int hp, int n, int isinc)
{
  sort(request,n);
  int ans[n+2];
  ans[0]=hp;
  int ind=1;
  int seektime=0;
  int  first=-1;
  
  for(int i=0; i<n; i++)
  {
    if(request[i] >= hp)
    {
      if(first == -1)
      {
        first=i;
        if(!isinc)
        {
         break;
        }
      }
      ans[ind]=request[i];
      //seektime+=(ans[ind]-ans[ind-1]);
      ind++;
    }
  }
  
  if(!isinc)
  {
   printf("Seek time :- %d\n",(hp+request[n-1]));
   printf("1  %d\n",hp);
   int ind=2;
   
   for(int i=first-1; i>=0; i--)
   {
     printf("%d\t%d\n",ind,request[i]);
     ind++;
   }
   
   printf("%d\t0\n",ind);
   
   for(int i=first; i<n; i++)
   {
     printf("%d\t%d\n",ind,request[i]);
     ind++;
   }
   
   return;
  }
  
  if(request[n-1] < maxsize)
  {
    ans[ind]=maxsize;
    //seektime+=(maxsize-request[n-1]);
    ind++;
  }
  
  for(int i=first-1; i>=0; i--)
  {
    ans[ind]=request[i];
    //seektime+=(maxsize-request[i]);
    ind++;
  }
  
  printf("Total seek time :- %d\n",(maxsize-hp)+(maxsize-request[0]));
  for(int i=0; i<n+2; i++)
  {
    printf("%d\t%d\n",i+1,ans[i]);
  }
  
  
}

void C_LOOK(int request[], int hp, int n, int isinc)
{
  sort(request,n);
  if(isinc)
  {
    int first=-1;
    int seektime;
   

    

    
    printf("1\t%d\n",hp);
    int ind=2;
    
    for(int i=0; i<n; i++)
    {
       if(request[i] >= hp)
       {
        if(first == -1)
        {
         first=i;
        }
        printf("%d\t%d\n",ind,request[i]);
       }
       ind++;
    }
    
    for(int i=0; i<first; i++)
    {
      printf("%d\t%d\n",ind,request[i]);
      ind++;
    }
    
    seektime=(request[n-1]-hp)+(request[n-1]-request[0])+(request[first-1]-request[0]);
    printf("Total seek time:- %d\n",seektime);
  }
  else
  {
   int first=-1;
   for(int i=0; i<n; i++)
   {
     if(request[i] >= hp)
     {
       first=i;
       break;
     }
   }
   printf("Total seek time:- %d\n",(hp-request[0])+(request[n-1]-request[0])+(request[n-1]-request[first]));
   printf("1\t%d\n",hp);
   int ind=2;
   
   for(int i=first-1; i>=0; i--)
   {
     printf("%d\t%d\n",ind,request[i]);
   }
   
  }
  
}

int main()
{
// algorithms to be implemented 
// SSTF
// SCAN 
// C-LOOK
while(1)
{
 int ch;
 int request[]={82,170,43,140,24,16,190};
 int n=7;
 int hp=50;
 
 printf("1) SSTF \n");
 printf("2) SCAN \n");
 printf("3) C-LOOK \n");
 printf("4) Exit\n");
 printf("Enter choice: \n");
 scanf("%d",&ch);
 if(ch == 1)
 {
    SSTF(request,hp,n);
 }
 else if(ch == 2)
 {
    SCAN(request,hp,n,0);
 }
 else if(ch == 3)
 {
   C_LOOK(request,hp,n,1);
 }
 else
 {
   break;
 }
 
}

return 0;
}
