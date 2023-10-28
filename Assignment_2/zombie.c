#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

int main()
{

 pid_t cpid=fork();
  
 if(cpid == -1)
 {
  perror("fork");
  exit(EXIT_FAILURE);
 }
 
 if(cpid == 0)
 {
   sleep(1);
   printf("\n");
   printf("Parent process id %d \n",getppid());
   printf("Child process id %d \n",getpid());
 }
 else
 {
   printf("This is parent process with pid %d\n",getpid());
   sleep(50);
   wait(NULL);
 }


return 0;
}
