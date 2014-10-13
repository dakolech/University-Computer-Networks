#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>

struct sockaddr_in myaddr, serv_addr;

int main ()
{
	char buf[100]="Wiadomosc";

	// struktura adresu własnego
	memset(&myaddr, 0, sizeof(struct sockaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY; // jakikolwiek adres
	myaddr.sin_port = 0; // -> jakikolwiek port wybrany przez system

	// struktura adresu serwera
	memset(&serv_addr, 0, sizeof(struct sockaddr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("150.254.32.145");
	serv_addr.sin_port = htons(atoi("13"));


	int sock = socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	bind(sock, (struct sockaddr*)&myaddr, sizeof(struct sockaddr));
	sendto(sock, buf, 1024, 0, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr));
	recvfrom(sock, buf, 1024, 0, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr));
	
	printf("Wiadomosc: %s", buf);
	close(sock);
	return 0;
}
