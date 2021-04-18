#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

struct client_conn_t;

void disc_handler(void)
{
	//crafting offer packet
	unsigned char *res_packet = (unsigned char *)malloc(65536);
	memset(res_packet, 0, sizeof(res_packet));

	struct ethhdr *eth = (struct ethhdr *)res_packet;
	struct iphdr *ip = (struct iphdr *)(res_packet + sizeof(struct ethhdr));
	struct udphdr *udp = (struct udphdr *)(res_packet + sizeof(struct ethhdr) + sizeof(struct iphdr));

	//ethhdr
	unsigned char dest[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	memcpy(eth->h_dest, dest, sizeof(eth->h_dest));
	
	unsigned char source[6] = { 0x41, 0x42, 0x43, 0x41, 0x42, 0x43 };
	memcpy(eth->h_dest, dest, sizeof(eth->h_dest));

	eth->h_proto = 0x800;

	//iphdr
	//udphdr
	//dhcp work

}

void req_handler(void)
{
	//send acknowledgement
}
