#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define DEBUG 1

char packet[USHRT_MAX];

struct client_conn_t
{
	int client_fd;
	struct sockaddr_in client;
	socklen_t length;
};

void *conn_handler(void *args)
{
	char ip_addr[INET_ADDRSTRLEN];
	struct client_conn_t *c = (struct client_conn_t *)args;

#if DEBUG		
	inet_ntop(AF_INET, &(c->client.sin_addr), ip_addr, INET_ADDRSTRLEN);
	printf("received connection from address at port: %s:%d\n", ip_addr, c->client.sin_port);
#endif

	pthread_exit(0);

	return NULL;

}	
