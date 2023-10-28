#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// sjf preemptive 
// round robin
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

typedef struct 
{
 int data;
 struct Node *next;
}Node;

typedef struct 
{
  Node *front;
  Node *rear;
}Queue;

int isEmpty(Queue* q)
{
  if(q->front == NULL )
  {
    return 1;
  }
  
 return 0;  
}

void enqueue(Queue* q, int val)
{
  Node* temp = (Node*)malloc(sizeof(Node));
  temp->data=val;
  temp->next=NULL;
  if(isEmpty(q))
  {
    q->front=temp;
    q->rear=temp;
    return;
  }
  else
  {
    q->rear->next=temp;
    q->rear=temp;
  }
}

int dequeue(Queue* q)
{
  if(isEmpty(q))
  {
    return -1;
  }
  else
  {
    int val=q->front->data;
    q->front=q->front->next;
    if(q->front == NULL)
    {
     q->rear=NULL;
    }
    
    return val;
  }
}

void initq(Queue *q)
{
 q->front=NULL;
 q->rear=NULL;
}

void SJF_P(Process arr[], int n)
{
  // sort on the basis of arrival time
  for(int i=0; i<n-1; i++)
  {
    for(int j=0; j<n-i-1; j++)
    {
      if(arr[j].arrivalT > arr[j+1].arrivalT)
      {
        Process temp=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
      }
    }
  }
  
  printf("ArrivalT\tBurstT\t\n");
  for(int i=0; i<n; i++)
  {
   printf("%d\t\t%d\n",arr[i].arrivalT,arr[i].burstT);
  }
  
  printf("\n");
  
  int brtime[n];
  for(int i=0; i<n; i++)
  {
    brtime[i]=arr[i].burstT;
  }
  
  int vis[n];
  
  for(int i=0; i<n; i++)
  {
    vis[i]=0;
  }
  
  int st=1;
  int viscnt=0;
  
  brtime[0]--;
  arr[0].CT=1;
  
  if(brtime[0] == 0)
  {
   vis[0]=1;
   viscnt++;
  }
  
  while(viscnt < n)
  {
    // for each one iteration in loop find the process with arrival time < st and with minimum burst time
    int mini=100000;
    int minind=-1;
    
    for(int i=0; i<n; i++)
    {
      if(!vis[i] && arr[i].arrivalT <= st && brtime[i] < mini)
      {
          minind=i;
          mini=brtime[i];
      }
    }
    
    st++;
    printf("%d  %d\n",minind,st);
    if(minind != -1)
    {
     brtime[minind]--;
     if(brtime[minind] == 0)
     {
        vis[minind]=1;
        viscnt++;
     }
     
     arr[minind].CT=st; 
    }
    
   
  }
  
  
  for(int i=0; i<n; i++)
  {
    printf("%d  %d\n",arr[i].pid,arr[i].CT);
  }
  
}

void Round_Robin(Process arr[], int n)
{
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<n-i-1; j++)
    {
      if(arr[j].arrivalT > arr[j+1].arrivalT)
      {
        Process temp=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
      }
    }
  }
  printf("Enter time quantum\n");
  int qtm;
  scanf("%d",&qtm);
  int brtime[n];
  
  for(int i=0; i<n; i++)
  {
   brtime[i]=arr[i].burstT;
  }
  int vis[n];
  
  for(int i=0; i<n; i++)
  {
   vis[i]=0;
  }
  
  vis[0]=1;
  printf("Before\n");
  
  int st=0;
  Queue q;
  initq(&q);
  printf("After\n");
  enqueue(&q,0);
  int viscnt=0;
  
  printf("Before loop\n");
  while(!isEmpty(&q))
  {
    printf("Inside loop\n");
    int ind=dequeue(&q);
    printf("%d\n",ind);
    int val=0;
    if(qtm <= brtime[ind])
    {
      val=qtm;
    }
    else
    {
      val=brtime[ind];
    }
    printf("%d    %d\n",val,st);
    
    brtime[ind]-=val;
   
    
    st=st+val;
    arr[ind].CT=st;
    
    for(int i=0; i<n; i++)
    {
      if(!vis[i] && arr[i].arrivalT <= st && i != ind && brtime[i] > 0)
      {
        enqueue(&q,i);
        vis[i]=1;
      }
    }
    
   
    
    if(brtime[ind] > 0)
    {
      enqueue(&q,ind);
    }
    
  }
  
  for(int i=0; i<n; i++)
  {
    printf("%d   %d\n",arr[i].pid,arr[i].CT);
  }
  
  
}


int main()
{
 printf("Enter no of process\n");
 int n;
 scanf("%d",&n);
 Process arr[n];
 printf("Enter arrival time of each process\n");
 for(int i=0; i<n; i++)
 {
   scanf("%d",&arr[i].arrivalT);
   arr[i].pid=i+1;
 }
 
    printf("Enter bursttime of each process\n");
    for(int i=0; i<n; i++)
    {
      scanf("%d",&arr[i].burstT);
    }
    
    
    
    //SJF_P(arr,n);
    Round_Robin(arr,n);


return 0;
}

