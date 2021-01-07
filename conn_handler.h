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
	struct dhcphdr *dhcp;
};

void *conn_handler(void *args)
{
	char ip_addr[INET_ADDRSTRLEN];
	struct client_conn_t *c = (struct client_conn_t *)args;
	
	c->eth = (struct ethhdr *)c->packet;
	c->ip = (struct iphdr *)(c->packet + sizeof(struct ethhdr));
	c->udp = (struct udphdr *)(c->packet + (sizeof(struct ethhdr) + sizeof(struct iphdr)));
	c->dhcp = (struct dhcphdr *)(c->packet + (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct udphdr)));

	if((int)c->ip->protocol == 17 && ntohs(c->udp->dest == 68))
	{
		
#if DEBUG		
		printf("received DHCP message\n");
#endif

		pthread_exit(0);
		return NULL;
	}
	else
	{
		pthread_exit(0);
		return NULL;
	}

}	
