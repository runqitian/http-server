#include "Server.h"
#include "HTTPSocket.h"
#include "HTTPResponse.h"
#include "HTTPRequest.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdexcept>
#include <thread>

#include <string>
#include <iostream>

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
		std::thread t(&httplib::Server::connectionThreadFunc, in_sockfd);
		t.detach();
	}
}

void httplib::Server::connectionThreadFunc(const int sockfd)
{
	printf("in thread, sockfd is %d\n", sockfd);
	httplib::HTTPSocket sock(sockfd);
	try
	{
		httplib::HTTPRequest *req = sock.readRequest();
		std::cout << "get request" << std::endl;
		std::cout << req -> toString() << std::endl;
		httplib::HTTPResponse resp;
		resp.setVersion("HTTP/1.1");
		resp.setStatus("200", "OK");
		std::string s("hello, world!");

		resp.setHeader("Content-Type", "text/html; charset=utf-8");
		resp.setHeader("Content-Length", std::to_string(s.size()));
		resp.setBody(s.c_str(), s.size());
		sock.sendResponse(resp);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		close(sockfd);
	}
}