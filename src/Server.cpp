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
	const int CONNECTION_TIMEOUT = 5;
	const int CONNECTION_MAX = 1000;
}

httplib::Server::Server()
{}

void httplib::Server::Get(const char *url, void (*func)(httplib::HTTPRequest&, httplib::HTTPResponse&))
{
	std::string *arg = new std::string;
	*arg = std::string("GET ") + std::string(url);
	registry_table[*arg] = func;
	std::cout << "GET " << std::string(url) << std::endl;
}

void httplib::Server::Post(const char *url, void (*func)(httplib::HTTPRequest&, httplib::HTTPResponse&))
{
	std::string *arg = new std::string;
	*arg = std::string("POST ") + std::string(url);
	registry_table[*arg] = func;
	std::cout << "POST " << std::string(url) << std::endl;
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
		httplib::HTTPResponse resp;
		// now only support http/1.0, no persistence connection.
		resp.setVersion("HTTP/1.0");
		resp.setHeader("Server", "httpserver");

		std::string tar(req -> getType() + " " + req -> getUrl());
		if (registry_table.find(tar) == registry_table.end())
		{
			resp.create404Response();
			sock.sendResponse(resp);
			close(sockfd);
		}
		else
		{
			void (*func)(httplib::HTTPRequest&, httplib::HTTPResponse&) = registry_table[tar];
			func(*req, resp);
			sock.sendResponse(resp);
			close(sockfd);
		}

		// // connection set up based on http/1.1 or http/1.0
		// resp.setVersion(req -> getVersion());
		// if (req -> getVersion() == "HTTP/1.1")
		// {
		// 	if (req -> getHeader("Connection") == "keep-alive")
		// 	{
		// 		keep-alive = true;
		// 		resp.setHeader("Connection", "keep-alive");
		// 		resp.setHeader("Keep-Alive", "timeout=5, max=1000");
		// 	}else{
		// 		keep-alive = false;
		// 		resp.setHeader("Connection", "close");
		// 	}
		// }else{
		// 	keep-alive = false;
		// }
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

