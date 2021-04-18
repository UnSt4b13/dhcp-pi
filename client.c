#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "dhcp_format.h"

#define PORT 67

int main(void)
{
	int sock;
	int opt = 1;
	struct sockaddr_in addr;
	struct dhcphdr dhcp;
	char packet[sizeof(dhcp)];
	
	dhcp.op = 1;
	dhcp.type = 6;
	dhcp.length = 6;
	dhcp.hops = 0;
	dhcp.xid = 0x41414141;
	dhcp.seconds = 0;
	dhcp.flags = 1;
	dhcp.ciaddr = 0x0;
	dhcp.yiaddr = 0x0;
	dhcp.siaddr = 0x0;
	dhcp.giaddr = 0x0;
	strncpy(dhcp.chaddr, "08:00:27:1c:17:b5", 15);
	memset(&dhcp.sname[0], 0, sizeof(dhcp.sname));
	memset(&dhcp.filename[0], 0, sizeof(dhcp.filename));

	//cookie
	memset(&dhcp.options[0], 0x63, 1);
	memset(&dhcp.options[1], 0x82, 1);
	memset(&dhcp.options[2], 0x53, 1);
	memset(&dhcp.options[3], 0x63, 1);	

	//message type
	memset(&dhcp.options[4], 0x35, 1);
	memset(&dhcp.options[5], 0x1, 1);
	memset(&dhcp.options[6], 0x1, 1);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);	
	addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

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

	if(sendto(sock, packet, strlen(packet), 0, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("sendto");
		exit(-1);
	}

	close(sock);
	
	return 0;

}
