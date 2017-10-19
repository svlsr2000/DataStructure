#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>




int
main( int argc, char *argv[] )
{
   char namebuff[32]={0};
   int pid;
   char * args[]={"./execute_child",namebuff,(char*)0};
   sprintf(namebuff,"/execute_child_sync-%d",getpid());

   sem_t *semaphore = sem_open(namebuff, O_CREAT|O_EXCL, 0644, 0);

   if (semaphore == SEM_FAILED) {
      perror("sem_open(3) error in parent process");
      fprintf(stderr, "sem_open() failed.  errno:%d\n", errno);
      exit(1);
   }
   pid =fork();

   if(pid ==-1)
   {
      perror ("First Fork call failure");
      sem_unlink(namebuff);
      return -1;
   }

   if(pid == 0)
   {
      fprintf(stderr,"Executing child \n");
      execv(args[0], args);
      exit(1);
   }
   else
   {
      fprintf(stderr,"Waiting for child to sync \n");
      sem_wait(semaphore);
      fprintf(stderr,"Child posted semaphore \n");
      sem_close(semaphore);
      sem_unlink(namebuff);
      exit(0);
   }

   return 0;
}
