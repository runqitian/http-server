#ifndef SERVER_H
#define SERVER_H

#include "HTTPRequest.h"
#include "HTTPResponse.h"

#include <stdint.h>
#include <unordered_map>

namespace httplib{

	class Server{
		
	public:
		const int max_connection = 50;
		std::unordered_map<std::string, void (*)(httplib::HTTPRequest&, httplib::HTTPResponse&)> registry_table;

		Server();
		void Get(const char *url, void (*func)(httplib::HTTPRequest&, httplib::HTTPResponse&));
		void Post(const char *url, void (*func)(httplib::HTTPRequest&, httplib::HTTPResponse&));
		void listen(const char* host, uint16_t port);
		void connectionThreadFunc(const int sockfd);
	};

}

#endif