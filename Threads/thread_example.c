#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

struct client_context {
  const char *name;
};

void * mythread(void * arg)
{
  struct client_context *ctx = (struct client_context *) arg;
  printf("[thread %s started]\n",ctx->name);
  free(ctx);
  return NULL; 
}

int main(int argc, char* argv[])
{
   char *b, *a;

   struct client_context *ctx = malloc(sizeof(struct client_context));
   struct client_context *ctx2 = malloc(sizeof(struct client_context));
   pthread_t id, id2;
   ctx->name = "mouse";
   ctx2->name = "rat";
   printf("Creating threads\n");
   pthread_create(&id, NULL, mythread, ctx);
   pthread_create(&id2, NULL, mythread, ctx2);
   pthread_join(id, (void**) &a);
   pthread_join(id2, (void**) &b);
   printf("End of the main program\n");
   return(0);
}
