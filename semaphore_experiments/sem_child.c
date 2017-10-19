#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>

#include <fcntl.h>

int
main( int argc, char *argv[] )
{
   sem_t *semaphore = sem_open(argv[1], O_EXCL, 0644, 0);

   if (semaphore == SEM_FAILED) {
      perror("sem_open(3) error in child process");
      sem_unlink(argv[3]);
      exit(1);
   }
   fprintf(stderr,"%s going to sleep for some time \n",argv[0]);
   sleep(5);
   fprintf(stderr,"Out of sleep going to post semaphore \n");
   sem_post(semaphore);
   return 0;
}
