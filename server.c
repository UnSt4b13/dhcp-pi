#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <limits.h>

#include "conn_handler.h"

#define PORT 8888

int main(void)
{
	int sock;
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);	

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock == 1)
	{
		perror("socket");
		exit(-1);
	}


	if(bind(sock, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("bind");
		exit(-1);
	}

	
	while(1)
	{
		pthread_t thread;
		struct client_conn_t client;

		if((recvfrom(sock, packet, USHRT_MAX - 1, 0, (struct sockaddr *)&client.client, &client.length)) == -1)
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







