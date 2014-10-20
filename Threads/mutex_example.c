#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

int i = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void * mythread(void * arg)
{
  pthread_mutex_lock(&mutex);
  i++;
  pthread_mutex_unlock(&mutex);
  return NULL; 
}

int main(int argc, char* argv[])
{
   char *b, *a;

   pthread_t id, id2;
   printf("i: %d\n",i);
   printf("Creating threads\n");
   pthread_create(&id, NULL, mythread, NULL);
   pthread_create(&id2, NULL, mythread, NULL);
   pthread_join(id, (void**) &a);
   pthread_join(id2, (void**) &b);
   printf("i: %d\n",i);
   return(0);
}
