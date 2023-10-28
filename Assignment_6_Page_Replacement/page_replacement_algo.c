#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define maxsize 3

typedef struct
{
 int data;
 struct Node *next;
 struct Node *prev;
}Node;

typedef struct
{
 Node *front;
 Node *rear;
}List;

void initL(List *q)
{
  q->front=NULL;
  q->rear=NULL;

}

void insertFront(List *l, int data)
{
   Node *temp= (Node*)malloc(sizeof(Node));
   temp->data=data;
   temp->next=NULL;
   temp->prev=NULL;

   if(l->front == NULL)
   {
      l->front=temp;
      l->rear=temp;
   }
   else
   {
      l->front->prev=temp;
      temp->next=l->front;
      l->front=temp;
   }
}

int removeBack(List *l)
{ 
  if(l->rear == NULL)
  {
    return -1;
  } 
  int data=l->rear->data;
  Node *temp=l->rear->prev;

  if(temp == NULL)
  {
     l->front=NULL;
     l->rear=NULL;
     return data;
  }

  temp->next=NULL;
  l->rear=temp;
  return data;
}

int getFront(List *l)
{
  if(l->front == NULL ) return -1;
  return l->front->data;
}


int getRear(List *l)
{
  if(l->rear == NULL) return -1;
  return l->rear->data;
}

int findinL(List *l, int data)
{
  Node *temp =l->front;
  while(temp != NULL)
  {
    if(temp->data == data) return 1;
    temp=temp->next;
  }

return 0;
}

void removeNode(List *l, Node *temp)
{
  Node *pw=temp->prev;
  Node *nxt=temp->next;

  if(pw && nxt)
  {
    pw->next=nxt;
    nxt->prev=pw;
  }
  else if(pw)
  {
    l->rear=pw;
    pw->next=NULL;
  }
  else if(nxt)
  {
    l->front=nxt;
    nxt->prev=NULL;
  }

  temp=NULL;
}

void printL(List *l)
{
  Node *temp=l->front;
  while(temp != NULL)
  {
    printf("%d\n",temp->data);
    temp=temp->next;
  }

  printf("--------------\n");
}
Node *getNode(List *l, int target)
{
 Node *temp=l->front;
 while(temp  && temp->data != target)
 {
    temp=temp->next;
 }

 return temp;
}

int findinBuffer(int arr[], int target, int n)
{
 for(int i=0; i<n; i++)
 {
   if(arr[i] == target)
   {
    return 1;
   }
 }

return 0;

}

void printbuffer(int arr[], int n)
{
 for(int i=n-1; i>=0; i--)
 {
  if(arr[i] != -1)
  {
    printf("%d\n",arr[i]);
  }
 }

printf("-------------------\n");

}

void FIFO(int refString[], int n,int m)
{
 int buffer[m];
 for(int i=0; i<m; i++)
 {
  buffer[i]=-1;
 }

 int ind=0;

 for(int i=0; i<n; i++)
 { 
    printf("%d :- \n",refString[i]);
    if(findinBuffer(buffer,refString[i],3))
    {
      printf("Hit\n");
    }     
    else{
        printf("Fault\n");
        buffer[ind%3]=refString[i];
        //printf("ind %d\n",ind);
        ind++;
    }
    printbuffer(buffer,m);
 }
}


void LRU(int refString[], int n, int m)
{
 List *l;
 initL(&l);
 for(int i=0; i<m; i++)
 {
   printf("%d\n",refString[i]);
   insertFront(&l,refString[i]);
   printf("Fault:- \n");
   printL(&l);
 }


 for(int i=m; i<n; i++)
 {
   printf("%d\n",refString[i]);

   if(findinL(&l,refString[i]))
   {
    printf("Hit\n");
    Node *temp=getNode(&l,refString[i]);
    removeNode(&l,temp);
    insertFront(&l,refString[i]);
   }
   else
   {
    printf("Fault\n");
    removeBack(&l);
    insertFront(&l,refString[i]);
   }
   
   printL(&l);
 }

}

int getEle(int buffer[], int n, int m, int refString[], int ind)
{
  int cnt=0;
  int cache[100];
  memset(cache,0,sizeof(cache));

  for(int i=ind; i<n; i++)
  {
    if(findinBuffer(buffer,refString[i],m) && !cache[refString[i]])
    {
      cnt++;
      cache[refString[i]]=1;
    }

    if(cnt == m)
    {
      return refString[i];
    }
  }

  for(int i=0; i<m; i++)
  {
   if(cache[buffer[i]] == 0)
   {
    return buffer[i];
   }
  }

}

void removeFromBuffer(int buffer[], int ele,int put,int m)
{
  for(int i=0; i<m; i++)
  {
    if(buffer[i] == ele)
    {
       buffer[i]=put;
       return;
    }
  }
}

void Optimal(int refString[], int n, int m)
{
   int buffer[m];
   memset(buffer,-1,sizeof(buffer));

  for(int i=0; i<m; i++)
  {
    printf("%d\n",refString[i]);
    printf("Fault\n");
    buffer[i]=refString[i];
    printbuffer(buffer,m); 
  }

  for(int i=m; i<n; i++)
  {
    printf("%d\n",refString[i]);

    if(findinBuffer(buffer,refString[i],m))
    {
      printf("Hit\n");
    }
    else
    {
      printf("Fault\n");
      int rind=getEle(buffer,n,m,refString,i);
      removeFromBuffer(buffer,rind,refString[i],m);
    }

    printbuffer(buffer,m);
  }

}

int main()
{
 // 
 int refString[]={7,0,1,2,0,3,0,4,2,3,0,3,1,2,0};
 Optimal(refString,15,3);




return 0;
}