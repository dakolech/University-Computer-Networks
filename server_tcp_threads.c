#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5

struct client_socket {
  const int *sck;
};



void* client_loop(void *arg) 
{
    struct client_socket *socket = (struct client_socket *) arg;
    //int nClientSocket = *((int*) arg);
    //printf("%s: [connection from %s]\n", argv[0], inet_ntoa((struct in_addr)stClientAddr.sin_addr));
    //printf("[connection from %s]\n", inet_ntoa((struct in_addr)stClientAddr.sin_addr));
    time_t now;
    struct tm *local;
    time (&now);
    local = localtime(&now);
    char buffer[50]="Wiadomosc";
    int n;
    //n = sprintf(buffer, "%s\n", asctime(local));
    //buffer="Wiadomosc";
    //write(nClientSocket, buffer, strlen(buffer+2));
    int rcvd;
    while(rcvd = recv(socket->sck, buffer, 1024, 0)) {
      send(socket->sck, buffer, rcvd, 0);
    }
    close(socket->sck);
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
   int nSocket;//, nClientSocket;
   //int  *nClientSocket = malloc(sizeof(int));
   int nBind, nListen;
   int nFoo = 1;
   socklen_t nTmp;
   struct sockaddr_in stAddr, stClientAddr;


   /* address structure */
   memset(&stAddr, 0, sizeof(struct sockaddr));
   stAddr.sin_family = AF_INET;
   stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   stAddr.sin_port = htons(SERVER_PORT);

   /* create a socket */
   nSocket = socket(AF_INET, SOCK_STREAM, 0);
   if (nSocket < 0)
   {
       fprintf(stderr, "%s: Can't create a socket.\n", argv[0]);
       exit(1);
   }
   setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo));

   /* bind a name to a socket */
   nBind = bind(nSocket, (struct sockaddr*)&stAddr, sizeof(struct sockaddr));
   if (nBind < 0)
   {
       fprintf(stderr, "%s: Can't bind a name to a socket.\n", argv[0]);
       exit(1);
   }
   /* specify queue size */
   nListen = listen(nSocket, QUEUE_SIZE);
   if (nListen < 0)
   {
       fprintf(stderr, "%s: Can't set queue size.\n", argv[0]);
   }
  
   while(1)
   {
       /* block for connection request */
       nTmp = sizeof(struct sockaddr);
       struct client_socket *socket = malloc(sizeof(struct client_socket));
       socket->sck = accept(nSocket, (struct sockaddr*)&stClientAddr, &nTmp);
       //nClientSocket = accept(nSocket, (struct sockaddr*)&stClientAddr, &nTmp);
       
       
       
       if (socket->sck < 0)
       {
           fprintf(stderr, "%s: Can't create a connection's socket.\n", argv[0]);
           exit(1);
       }
    
	pthread_t id;
	char *a;
	pthread_create(&id, NULL, client_loop, socket);
	pthread_join(id, (void**) &a);

    }

   close(nSocket);
   return(0);
}
