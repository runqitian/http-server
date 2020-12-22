#include "Server.h"
#include "HTTPSocket.h"
#include "HTTPResponse.h"
#include "HTTPRequest.h"
#include "Utils.h"

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
#include <mutex>

namespace httplib{
	int thread_count = 0;
	std::mutex thread_lock;
}

httplib::Server::Server()
{
	httplib::initializeGlobalVar();
}

void httplib::Server::Get(const char *url, void (*func)(httplib::HTTPRequest&, httplib::HTTPResponse&))
{
	std::string *arg = new std::string;
	*arg = std::string("GET ") + std::string(url);
	registry_table[*arg] = func;
	std::cout << "GET " << std::string(url) << std::endl;
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
		std::thread t(&httplib::Server::connectionThreadFunc, this, in_sockfd);
		t.detach();
	}
}

void httplib::Server::connectionThreadFunc(const int sockfd)
{
	thread_lock.lock();
	thread_count += 1;
	thread_lock.unlock();
	printf("current thread count %d, sockfd is %d\n", thread_count, sockfd);
	httplib::HTTPSocket sock(sockfd);
	try
	{
		httplib::HTTPRequest *req = sock.readRequest();

		std::cout << req -> getType() << " " << req -> getUrl() << std::endl;

		std::string tar(req -> getType() + " " + req -> getUrl());

		if (registry_table.find(tar) == registry_table.end())
		{
			printf("not found\n");
			return;
		}

		void (*func)(httplib::HTTPRequest&, httplib::HTTPResponse&) = registry_table[tar];
		httplib::HTTPResponse resp;
		func(*req, resp);
		sock.sendResponse(resp);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		close(sockfd);
	}
	thread_lock.lock();
	thread_count -= 1;
	thread_lock.unlock();
}