#ifndef SERVER_H
#define SERVER_H
#include <stdint.h>

namespace httplib{

	class Server{
		
	public:
		const int max_connection = 50;

		Server();
		void listen(const char* host, uint16_t port);
		static void connectionThreadFunc(const int sockfd);
	};

}

#endif