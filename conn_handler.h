#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#define DEBUG 1

struct client_conn_t
{
	int client_fd;
	struct sockaddr_in client;
	socklen_t length;
	char packet[65536];
	struct ethhdr *eth;
	struct iphdr *ip;
	struct udphdr *udp;
};

void *conn_handler(void *args)
{
	struct client_conn_t *c = (struct client_conn_t *)args;
	
	c->eth = (struct ethhdr *)c->packet;
	c->ip = (struct iphdr *)(c->packet + sizeof(struct ethhdr));
	c->udp = (struct udphdr *)(c->packet + (sizeof(struct ethhdr) + sizeof(struct iphdr)));
	
#if DEBUG		
	if(c->ip->protocol == 1)
	{
		c->client.sin_addr.s_addr = c->ip->saddr;
		printf("received ping from: %s\n", inet_ntoa(c->client.sin_addr));
	}
#endif

	pthread_exit(0);

	return NULL;

}	
