#include "Server.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdexcept>
#include <thread>

httplib::Server::Server()
{

}


void httplib::Server::listen(const char* host, uint16_t port)
{	
	// build socket address struct
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	struct hostent *hostinfo;
	hostinfo = gethostbyname(host);
	if (hostinfo == NULL)
	{
		throw std::runtime_error("host invalid!");
	}
	sa.sin_addr = *(struct in_addr *) hostinfo->h_addr;

	// set up server socket
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		throw std::runtime_error("failed to create socket!");
	}
	if (bind(sockfd, (struct sockaddr *)&sa, sizeof(sa)) < 0)
	{
		throw std::runtime_error("failed to bind socket!");
	}
	if (::listen(sockfd, this -> max_connection) == -1)
	{
		throw std::runtime_error("socket failed to listen!");
	}
	printf("server is listening on %s:%d\n", host, port);
	fflush(stdout);

	// listen for connection
	while (true)
	{
		int in_sockfd;
		if ((in_sockfd = accept(sockfd, NULL, NULL)) < 0)
		{
			printf("connection failed\n");
			continue;
		}
		std::thread t(&httplib::Server::http_connection_thread, in_sockfd);
		t.detach();
	}
}

void httplib::Server::http_connection_thread(const int sockfd)
{
	printf("in thread, sockfd is %d\n", sockfd);
}