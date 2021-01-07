#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "dhcp_format.h"

#define PORT 68

int main(void)
{
	int sock;
	int opt = 1;
	struct sockadhcpr_in adhcpr;
	struct dhcphdr dhcp;
	char packet[sizeof(dhcp)];
	
	dhcp.op = 1;
	dhcp.type = 6;
	dhcp.length = 6;
	dhcp.hops = 0;
	dhcp.xid = 0x41414141;
	dhcp.seconds = 0;
	dhcp.flags = 1;
	dhcp.ciadhcpr = 0x0;
	dhcp.yiadhcpr = 0x0;
	dhcp.siadhcpr = 0x0;

	strncpy(dhcp.chadhcpr, "ABCDEF", 13);
	strncpy(dhcp.sname, "UBUNTU", 6);

	memset(&dhcp.filename[0], 0, sizeof(dhcp.filename));
	memset(&dhcp.options[0], 0, sizeof(dhcp.options));	

	adhcpr.sin_family = AF_INET;
	adhcpr.sin_port = htons(PORT);	

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock == -1)
	{
		perror("socket");
		exit(-1);
	}

	
	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt)) == -1)
	{
		perror("setsockopt");
		exit(-1);
	}

	memcpy(packet, &dhcp, sizeof(dhcp));

	if(sendto(sock, packet, strlen(packet), 0, (struct sockadhcpr *)&adhcpr, sizeof(adhcpr)) == -1)
	{
		perror("sendto");
		exit(-1);
	}

	close(sock);
	
	return 0;

}
