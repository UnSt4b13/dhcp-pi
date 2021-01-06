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
	struct sockaddr_in addr;
	struct dhcp_discover dd;
	char packet[sizeof(dd)];
	
	dd.op = 1;
	dd.type = 6;
	dd.length = 6;
	dd.hops = 0;
	dd.xid = 0x41414141;
	dd.seconds = 0;
	dd.flags = 1;
	dd.ciaddr = 0x0;
	dd.yiaddr = 0x0;
	dd.siaddr = 0x0;

	strncpy(dd.chaddr, "<MAC ADDRESS>", 13);
	strncpy(dd.sname, "UBUNTU", 6);

	memset(&dd.filename[0], 0, sizeof(dd.filename));
	memset(&dd.options[0], 0, sizeof(dd.options));	

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);	

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

	memcpy(packet, &dd, sizeof(dd));

	if(sendto(sock, packet, strlen(packet), 0, (struct sockaddr *)&addr, sizeof(addr.sin_zero)) == -1)
	{
		perror("sendto");
		exit(-1);
	}

	close(sock);
	
	return 0;

}
