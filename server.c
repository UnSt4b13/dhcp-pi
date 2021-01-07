#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "conn_handler.h"

int main(void)
{
	int sock;

	sock = socket(AF_PACKET, SOCK_RAW, htonl(ETH_P_ALL));
	if(sock == -1)
	{
		perror("socket");
		exit(-1);
	}

	
	while(1)
	{
		pthread_t thread;
		struct client_conn_t client;

		if((recvfrom(sock, client.packet, 65536, 0, NULL, NULL)) == -1)
		{
			perror("recvfrom");
			continue;
		}

		if(pthread_create(&thread, NULL, conn_handler, &client))
		{
			perror("pthread_create");
			continue;
		}

		if(pthread_detach(thread) != 0)
		{
			perror("pthread_detach");
		}
	}

	return 0;

}







