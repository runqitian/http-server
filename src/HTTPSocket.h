#ifndef HTTPSOCKET_H
#define HTTPSOCKET_H

#include <string>
#include "HTTPRequest.h"
#include "HTTPResponse.h"

namespace httplib {

	class HTTPSocket {
	public:
		int sockfd;

		HTTPSocket(int sockfd);
		HTTPSocket(HTTPSocket& sock) = delete;
		~HTTPSocket();

		httplib::HTTPRequest* readRequest();
		void sendResponse(httplib::HTTPResponse &resp);
	private:
		static const size_t BUFF_SIZE = 64 * 1024;
		char * sbuff;
		size_t sbuff_size;

		std::string readline();
		void readBytes(char *dest, size_t len);
		void sendBytes(const char *msg, const size_t len);

		void _readHeader(httplib::HTTPRequest &req);
		void _readBody(httplib::HTTPRequest &req);
		void _extractBodyInfo(httplib::HTTPRequest &req);

		bool _checkRequestValid(const std::string &type, const std::string &version);
	};

}

#endif