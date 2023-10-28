// Algorithms 
// Vishal SHarad Patil 33158
// 1) First come first serve
// 2) Shortest Job first Non preamptive
// 3) Shortest Job firt preamptive
// 4) Priority based preemptive
// 5) Priority based non preemptive
// 6) Round Robin

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//#include <queue.h>

struct Node
{
  int data;
  struct Node* next;
};

struct Node *front = NULL;
struct Node *rear  = NULL;

void  Q_push(int x)
{
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data=x;
  new_node->next=NULL;

  if(front == NULL)
  {
    front=new_node;
    rear=new_node;
  }
  else
  {
    rear->next=new_node;
    rear=rear->next;
  }
}

int Q_pop()
{
  if(front == NULL) return -1;

  int val=front->data;
  front=front->next;
  return val; 
}

int Q_get_front()
{
 if(front == NULL) return -1;
 int val=front->data;
 return val;

}

int isempty()
{
 if(front == NULL) return 1;
 return 0;
}


int max(int a, int b)
{
  return a>b ? a:b;

}

typedef struct 
{
 int pid;
 int arrivalT;
 int burstT;
 int priority;
 int CT;
 int TAT;
 int WT;
}Process;

void draw_gyan(Process arr[], int n, int maxt)
{
for(int i=0; i<n; i++)
{
  for(int j=0; j<n-i-1; j++)
  {
    if(arr[j].CT > arr[j+1].CT)
    {
      Process temp=arr[j];
      arr[j]=arr[j+1];
      arr[j+1]=temp;
    }
  }
}
 printf("Pid\tarrival-time\tburst-time\tcompletion-time\tTAT\tWT\n");
  for(int i=0; i<n; i++)
  {
  printf("%d\t\t%d\t\t%d\t%d\t\t%d\t%d",arr[i].pid,arr[i].arrivalT,arr[i].burstT,arr[i].CT,arr[i].TAT,arr[i].WT);
  printf("\n");
  }

  printf("Gannt chart\n");

  for(int i=0; i<maxt; i++)
  {
    printf("--");
  }
  printf("\n");
  printf("|");
  printf("%d",arr[0].pid);
  for(int i=0; i<arr[0].CT; i++)
  {
    printf(" ");
  }
  printf("|");
  for(int i=1; i<n; i++)
  {
    printf("%d",arr[i].pid);
    for(int j=arr[i-1].CT; j<arr[i].CT; j++)
    {
      printf(" ");
    }
    printf("| ");
  }
  printf("\n");
  for(int i=0; i<maxt; i++)
  {
    printf("--");
  }
  printf("\n");
  printf("0");
  //printf("%d",arr[0].pid)
  for(int i=0; i<arr[0].CT; i++)
  {
    printf(" ");
  }
  printf("%d",arr[0].CT);
  for(int i=1; i<n; i++)
  {
    printf(" ");
    for(int j=arr[i-1].CT; j<arr[i].CT; j++)
    {
      printf(" ");
    }
    printf("%d ",arr[i].CT);
  }

printf("\n");
}

void FCFS(Process arr[], int n)
{
  // sort based on arrival time
  for(int i=0; i<n;i++)
  {
    for(int j=0; j<n-i-1;j++)
    {
      if(arr[j].arrivalT > arr[j+1].arrivalT)
      {
        Process temp=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
      }
    }
  }
  // calculate completion time
  int start=0;
  int maxt=0;

  for(int i=0; i<n; i++)
  {
   arr[i].CT=max(arr[i].arrivalT,start)+arr[i].burstT;
   start=arr[i].CT;
   maxt=max(maxt,start);
   arr[i].TAT=arr[i].CT-arr[i].arrivalT;
   arr[i].WT=arr[i].TAT-arr[i].burstT;
  }
  
  draw_gyan(arr,n,maxt);
  
}

void SJF_P(Process arr[], int n)
{

  for(int i=0; i<n;i++)
  {
    for(int j=0; j<n-i-1;j++)
    {
      if(arr[j].arrivalT == arr[j+1].arrivalT)
      {
         if(arr[j].burstT > arr[j+1].burstT)
         {
            Process temp=arr[j+1];
            arr[j+1]=arr[j];
            arr[j]=temp;
         }
      }
      else if(arr[j].arrivalT > arr[j+1].arrivalT)
      {
          Process temp=arr[j+1];
          arr[j+1]=arr[j];
          arr[j]=temp;
      }
    }
  }
  
  // printf("Pid  arrival-time  burst-time completion-time  TAT WT\n");
  // for(int i=0; i<n; i++)
  // {
  //   printf("%d  %d  %d  %d  %d  %d\n",arr[i].pid,arr[i].arrivalT,arr[i].burstT,arr[i].CT,arr[i].TAT,arr[i].WT);

  // }

  int brtime[n];
  for(int i=0; i<n; i++)
  {
    brtime[i]=arr[i].burstT;
  }

  int visited[n];
  for(int i=0; i<n; i++)
  {
    visited[i]=0;
  }

  int st=arr[0].arrivalT+1;
  brtime[0]-=1;
  int viscnt=0;

  if(brtime[0] == 0)
  {
    visited[0]=1;
    viscnt++;
  }

  arr[0].CT=1;
  int maxt=0;

  while(1)
  {
  int minibrst=100001;
  int minind=-1;
  printf("%d\n",st);
  for(int i=0; i<n; i++)
  {
    //printf("%d   %d\n",arr[i].arrivalT,brtime[i]);
    if(!visited[i] && arr[i].arrivalT <= st && brtime[i]<minibrst)
    {
      minind=i;
      minibrst=brtime[i];
    }
  }

  st++;
  if(minind != -1 && !visited[minind])
  {
    //printf("minind %d  st %d ",minind,st);
    arr[minind].CT=st;
    brtime[minind]-=1;
    if(brtime[minind] == 0)
    {
     visited[minind]=1;
     viscnt++;
    }
  }

   if(viscnt == n)
   {
    break;
   }

  //printf("%d   %d\n",minind,minibrst);
  }

 for(int i=0; i<n; i++)
 {
   maxt=max(maxt,arr[i].CT);
  arr[i].TAT=arr[i].CT-arr[i].arrivalT;
  arr[i].WT=arr[i].TAT-arr[i].burstT;
 }
 printf("\n");
draw_gyan(arr,n,maxt);

}


void SJF_NP(Process arr[], int n)
{
  for(int i=0; i<n;i++)
  {
    for(int j=0; j<n-i-1;j++)
    {
      if(arr[j].arrivalT == arr[j+1].arrivalT)
      {
         if(arr[j].burstT > arr[j+1].burstT)
         {
            Process temp=arr[j+1];
            arr[j+1]=arr[j];
            arr[j]=temp;
         }
      }
      else if(arr[j].arrivalT > arr[j+1].arrivalT)
      {
          Process temp=arr[j+1];
          arr[j+1]=arr[j];
          arr[j]=temp;
      }
    }
  }

 int total_process=1;
 arr[0].CT=arr[0].arrivalT+arr[0].burstT;
 int cmp=arr[0].CT;
 int vis[n];

 for(int i=0; i<n; i++)
 {
  vis[i]=0;
 }

 vis[0]=1;

 while(total_process < n)
 {
   int ind=-1;
   int mini=1000;

   for(int j=1; j<n; j++)
   {
    //printf("%d  %d  %d  %d  %d\n",vis[j],arr[j].arrivalT,cmp,arr[j].priority,mini);
    if(!vis[j] && arr[j].arrivalT <= cmp && arr[j].burstT < mini)
    {
      mini=arr[j].burstT;
      ind=j;
    }
    else if(arr[j].arrivalT > cmp)
    {
      break;
    }

   }

   printf("%d\n",ind);
   if(ind == -1)
   {
    cmp++;
   }
   else
   {
    arr[ind].CT=max(arr[ind].arrivalT,cmp)+arr[ind].burstT;
    cmp=arr[ind].CT;
    vis[ind]=1;
    total_process++;
   }
 }


int maxt=0;

for(int i=0; i<n; i++)
{
   maxt=max(maxt,arr[i].CT);
  arr[i].TAT=arr[i].CT-arr[i].arrivalT;
  arr[i].WT=arr[i].TAT-arr[i].burstT;
}

printf("\n");
draw_gyan(arr,n,maxt);

}


void Priority_P(Process arr[], int n)
{
    printf("Enter priority of each process\n");
    for(int i=0; i<n; i++)
    {
      scanf("%d",&arr[i].priority);
    }
  for(int i=0; i<n;i++)
  {
    for(int j=0; j<n-i-1;j++)
    {
      if(arr[j].arrivalT == arr[j+1].arrivalT)
      {
         if(arr[j].priority > arr[j+1].priority)
         {
            Process temp=arr[j+1];
            arr[j+1]=arr[j];
            arr[j]=temp;
         }
      }
      else if(arr[j].arrivalT > arr[j+1].arrivalT)
      {
          Process temp=arr[j+1];
          arr[j+1]=arr[j];
          arr[j]=temp;
      }
    }
  }
  
  // printf("Pid  arrival-time  burst-time completion-time  TAT WT\n");
  // for(int i=0; i<n; i++)
  // {
  //   printf("%d  %d  %d  %d  %d  %d\n",arr[i].pid,arr[i].arrivalT,arr[i].burstT,arr[i].CT,arr[i].TAT,arr[i].WT);

  // }

  int brtime[n];
  for(int i=0; i<n; i++)
  {
    brtime[i]=arr[i].burstT;
  }

  int visited[n];
  for(int i=0; i<n; i++)
  {
    visited[i]=0;
  }

  int st=arr[0].arrivalT+1;
  brtime[0]-=1;
  int viscnt=0;

  if(brtime[0] == 0)
  {
    visited[0]=1;
    viscnt++;
  }

  arr[0].CT=1;
  int maxt=0;

  while(1)
  {
  int minibrst=100001;
  int minind=-1;
  //printf("%d\n",st);
  for(int i=0; i<n; i++)
  {
    //printf("%d   %d\n",arr[i].arrivalT,brtime[i]);
    if(!visited[i] && arr[i].arrivalT <= st && arr[i].priority<minibrst)
    {
      minind=i;
      minibrst=arr[i].priority;
    }
  }

  st++;
  if(minind != -1 && !visited[minind])
  {
    //printf("minind %d  st %d ",minind,st);
    arr[minind].CT=st;
    brtime[minind]-=1;
    if(brtime[minind] == 0)
    {
     visited[minind]=1;
     viscnt++;
    }
  }

   if(viscnt == n)
   {
    break;
   }

  //printf("%d   %d\n",minind,minibrst);
  }

 for(int i=0; i<n; i++)
 {
   maxt=max(maxt,arr[i].CT);
  arr[i].TAT=arr[i].CT-arr[i].arrivalT;
  arr[i].WT=arr[i].TAT-arr[i].burstT;
 }
 printf("\n");
draw_gyan(arr,n,maxt);

}



void Priority_NP(Process arr[], int n)
{
    printf("Enter priority of each process\n");
    for(int i=0; i<n; i++)
    {
      scanf("%d",&arr[i].priority);
    }
 // sort based on arrival time

 for(int i=0; i<n; i++)
 {
  for(int j=0; j<n-i-1; j++)
  {
    if(arr[j].arrivalT > arr[j+1].arrivalT)
    {
      Process p=arr[j+1];
      arr[j+1]=arr[j];
      arr[j]=p;  
    }
  }
 }

 int total_process=1;

 arr[0].CT=arr[0].arrivalT+arr[0].burstT;
 int cmp=arr[0].CT;
 int vis[n];

 for(int i=0; i<n; i++)
 {
  vis[i]=0;
 }

 vis[0]=1;

 while(total_process < n)
 {
   int ind=-1;
   int mini=1000;
   for(int j=1; j<n; j++)
   {
    printf("%d  %d  %d  %d  %d\n",vis[j],arr[j].arrivalT,cmp,arr[j].priority,mini);
    if(!vis[j] && arr[j].arrivalT <= cmp && arr[j].priority < mini)
    {
      mini=arr[j].priority;
      ind=j;
    }
    else if(arr[j].arrivalT > cmp)
    {
      break;
    }

   }

   printf("%d\n",ind);
   if(ind == -1)
   {
    cmp++;
   }
   else
   {
    arr[ind].CT=max(arr[ind].arrivalT,cmp)+arr[ind].burstT;
    cmp=arr[ind].CT;
    vis[ind]=1;
    total_process++;
   }
 }

for(int i=0; i<n; i++)
{
  arr[i].TAT=arr[i].CT-arr[i].arrivalT;
  arr[i].WT=arr[i].TAT-arr[i].burstT;
}

printf("\n");
draw_gyan(arr,n,cmp);

}

int min(int v1, int v2)
{
  if(v1 < v2) return v1;
  return v2;
}

void Round_Robin(Process arr[],int t,int n)
{
  printf("Enter time quantum :- ");
  int qt; scanf("%d",&qt);
  for(int i=0; i<n;i++)
  {
    for(int j=0; j<n-i-1;j++)
    {
      if(arr[j].arrivalT == arr[j+1].arrivalT)
      {
         if(arr[j].burstT > arr[j+1].burstT)
         {
            Process temp=arr[j+1];
            arr[j+1]=arr[j];
            arr[j]=temp;
         }
      }
      else if(arr[j].arrivalT > arr[j+1].arrivalT)
      {
          Process temp=arr[j+1];
          arr[j+1]=arr[j];
          arr[j]=temp;
      }
    }
  }

  int brtime[n];
  int maxt=0;

  for(int i=0; i<n; i++)
  {
    brtime[i]=arr[i].burstT;
  }

  Q_push(0);
  int st=0;
  int visited[n];
  for(int i=0; i<n; i++)
  {
    visited[i]=0;
  }
  int viscnt=0;

  while(!isempty())
  {
    int ind=Q_pop();
    
    //printf("ind %d ",ind);
    //printf("st %d  brtime %d\n",st,brtime[ind]);
    //printf("v1 %d  v2 %d\n",(st+qt),(brtime[ind]+st));
    int sub=min(qt,brtime[ind]);
    //printf("%d\n",ind);
    int currt=min(st+qt,st+brtime[ind]);
    st=currt;
    //printf("st %d   ind  %d   brtime  \n",st,ind,brtime[ind]); 
    brtime[ind]-=sub;
    visited[ind]=1;
    arr[ind].CT=st;
    if(brtime[ind] <= 0)
    {
      viscnt++;
    }

    // if(viscnt == n)
    // {
    //   break;
    // }
    if(viscnt < n){
    for(int i=0; i<n; i++)
    {
      //printf("%d ",brtime[i]);
      if(!visited[i] && i != ind && arr[i].arrivalT <= st)
      {
        //printf("%d ",i);
        Q_push(i);
        visited[i]=1;
      }
    }

    }
    //printf("\n");

    //printf("%d",brtime[ind]);
    if(brtime[ind] > 0)
    {
      Q_push(ind);
    }
    
  }

  for(int i=0; i<n; i++)
  {
    arr[i].TAT=arr[i].CT-arr[i].arrivalT;
    arr[i].WT=arr[i].TAT-arr[i].burstT;
    maxt=max(maxt,arr[i].CT);
  }
  printf("\n");
  draw_gyan(arr,n,maxt);

}

int main()
{
    printf("Enter no of processes you want\n");
    int n; 
    scanf("%d",&n);
    Process Processes[n];
    
    printf("Enter arrival time of each process\n");
    for(int i=0; i<n; i++)
    {
      scanf("%d",&Processes[i].arrivalT);
      Processes[i].pid=i;
    }
    
    printf("Enter bursttime of each process\n");
    for(int i=0; i<n; i++)
    {
      scanf("%d",&Processes[i].burstT);
    }
    
    

 for(int i=0; i<n; i++)
 {
  printf("%d  %d  %d \n",Processes[i].pid,Processes[i].arrivalT,Processes[i].burstT);
 }

    
  while(1)
  {
    printf("Choose the algorithm that you want\n");
    printf("1) First come first serve\n");
    printf("2) SJF Preeamptive\n");
    printf("3) SJF Non Preeamptive\n");
    printf("4) Priority preeamptive\n");
    printf("5) Priority non preeamptive\n");
    printf("6) Round Robin\n");
    printf("7) Exit\n");
    int ch; 
    scanf("%d",&ch);
    if(ch == 1)
    {
      FCFS(Processes,n);
    }
    else if(ch == 2)
    {
      SJF_P(Processes,n);
    }
    else if(ch == 3)
    {
      SJF_NP(Processes,n);
    }
    else if(ch == 4)
    {
      Priority_P(Processes,n);
    }
    else if(ch == 5)
    {
     Priority_NP(Processes,n);
    }
    else if(ch == 6)
    {
     //printf("Enter time quantum\n");
     //int t; scanf("%d",&t);
     int t=0;
     Round_Robin(Processes,t,n);
    }
    else
    {
      printf("Exiting");
      break;
    }
    
    
  
  }


}
